#include "aes.h"
#include "databoxes.h"
#include <stdio.h>

void SubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    int i, j;
    unsigned char x, y;
    for(i = 0; i < STATE_COLUMNS; i++)
    {
        for(j = 0; j < STATE_ROWS; j++)
        {
            x = (state[i][j] & 0xF0) >> 4;
            y = (state[i][j] & 0x0F);
            state[i][j] = s[x][y];
        }
    }
}

void ShiftRows(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    int temp[4];
    for (int row = 1; row < STATE_ROWS; row++)
    {
        for (int col = 0; col < STATE_COLUMNS; col++)
            temp[col] = state[row][col];

        for (int col = 0; col < STATE_COLUMNS; col++)
            state[row][col] = temp[(col+row)%4];
    }
}

void InvShiftRows(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    int temp[4];
    for (int row = 1; row < STATE_ROWS; row++)
    {
        for (int col = 0; col < STATE_COLUMNS; col++)
            temp[col] = state[row][col];

        for (int col = 0; col < STATE_COLUMNS; col++)
            state[row][col] = temp[(col+(4-row))%4];
    }
}

void MixColumns(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    BYTE temp[4];

    // AES chosen modulus when values exceed 255
    int modulo = (1<<8) + (1<<4) + (1<<3) + (1<<1) + 1;

    for (int col = 0; col < STATE_COLUMNS; col++)
    {
        for (int row = 0; row < STATE_ROWS; row++)
            temp[row] = state[row][col];

        for (int row = 0; row < STATE_ROWS; row++)
        {
            int result = 0;
            for (int i = 0; i < STATE_ROWS; i++)
            {
                if (ColMixer[row][i]&1)
                    result ^= temp[i];
                if (ColMixer[row][i]&2)
                    result ^= (temp[i]<<1);
            }

            if (result >= 1<<8)
                result ^= modulo;

            state[row][col] = result;
        }
    }
}

void InvMixColumns(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    BYTE temp[4];

    // AES chosen modulus when values exceed 255
    int modulo = (1<<8) + (1<<4) + (1<<3) + (1<<1) + 1;

    for (int col = 0; col < STATE_COLUMNS; col++)
    {
        for (int row = 0; row < STATE_ROWS; row++)
            temp[row] = state[row][col];

        for (int row = 0; row < STATE_ROWS; row++)
        {
            int result = 0;
            for (int i = 0; i < STATE_ROWS; i++)
            {
                if (InvColMixer[row][i]&1)
                    result ^= temp[i];
                if (InvColMixer[row][i]&2)
                    result ^= temp[i]<<1;
                if (InvColMixer[row][i]&4)
                    result ^= temp[i]<<2;
                if (InvColMixer[row][i]&8)
                    result ^= temp[i]<<3;
            }

            if (result >= 1<<8)
                result ^= modulo;

            state[row][col] = result;
        }
    }
}

void AddRoundKeys(WORD keys[WORDS_OF_EXPANSION], BYTE state[STATE_ROWS][STATE_COLUMNS], int round)
{
    int i;
    for(i = 0; i < STATE_COLUMNS; i++)
    {
        state[0][i] = state[0][i] ^ ((keys[round*STATE_COLUMNS + i] & 0xFF000000 ) >> 24);
        state[1][i] = state[1][i] ^ ((keys[round*STATE_COLUMNS + i] & 0x00FF0000) >> 16);
        state[2][i] = state[2][i] ^ ((keys[round*STATE_COLUMNS + i] & 0x0000FF00) >> 8);
        state[3][i] = state[3][i] ^ (keys[round*STATE_COLUMNS + i] & 0x000000FF);
    }
}

void KeyExpansion(BYTE key[NUMBER_WORDS_KEY], WORD w[WORDS_OF_EXPANSION])
{
    unsigned int temp;
    int i = 0;

    while(i < NUMBER_WORDS_KEY)
    {
        w[i] = (key[(4*i)+3]) | (key[(4*i)+2] << 8) | (key[(4*i)+1] << 16) | (key[(4*i)] << 24);
        i += 1;
    }

    i = NUMBER_WORDS_KEY;

    while(i < (STATE_COLUMNS * (NUMBER_ROUNDS + 1)))
    {
        temp = w[i-1];
        if(i % NUMBER_WORDS_KEY == 0)
        {
            temp = SubWord(RotWord(temp)) ^ (rcon[i/NUMBER_WORDS_KEY] << 6*4);
        }
        else if(NUMBER_WORDS_KEY > 6 && i % NUMBER_WORDS_KEY == 4)
        {
            temp = SubWord(temp);
        }
        w[i] = w[i-NUMBER_WORDS_KEY] ^ temp;
        i++;
    }

}

unsigned int SubWord(WORD word)
{
    BYTE temp, x, y;
    unsigned int newWord;
    BYTE subs[4];
    int i;

    for(i = 0; i < 4; i++)
    {
        temp = (word & (0xFF << (8*i))) >> (8*i);
        x = (temp & 0xF0) >> 4;
        y = (temp & 0x0F);
        subs[i] = s[x][y];;
    }

    newWord = subs[0] | (subs[1] << 8) | (subs[2] << 16) | (subs[3] << 24);


    return newWord;
}

unsigned int RotWord(WORD word)
{
    BYTE temp;

    temp = (word & 0xFF000000) >> (6*4);
    word <<= 8;
    word |= (temp & 0x000000FF);

    return word; 
}

void InvSubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS])
{
    int i, j;
    unsigned char x,y;

    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            x = (state[i][j] & 0xF0) >> 4;
            y = (state[i][j] & 0x0F);
            state[i][j] = inv_s[x][y];
        }
    }    
}
