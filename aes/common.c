#ifndef COMMON_C
#define COMMON_C

#include "aes.h"
#include "databoxes.h"

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

void ShiftRows(BYTE** state)
{

}

void MixColumns(BYTE** state)
{

}

void AddRoundKeys(unsigned int key, BYTE** state)
{

}



void KeyExpansion(unsigned int key, unsigned int w)
{
    unsigned int temp;
    int i = 0;

    while(i < NUMBER_WORDS_KEY)
    {
        
    }

    i = NUMBER_WORDS_KEY;
}

unsigned int SubWord(unsigned int word)
{
    BYTE temp, x, y;
    unsigned int newWord;
    int i;

    for(i = 0; i < ; i++)
    {
        temp = (word & (0xFF << (8*i))) >> (8*i);
        x = (temp & 0xF0) >> 4;
        y = (temp & 0x0F);
        newWord |= (s[x][y] << (8*i));
    }

    return newWord;
}

unsigned int RotWord(unsigned int word)
{
    BYTE temp;

    temp = (word & 0xFF000000) >> (6*4);
    word <<= 8;
    word |= (temp & 0x000000FF);

    return word; 
}

#endif
