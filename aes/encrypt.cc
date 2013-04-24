#include "aes.h"


void encryt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], WORD cipherKey[NUMBER_WORDS_KEY])
{
    unsigned int expandedKeys[WORDS_OF_EXPANSION];

    int i, j, k;
    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            out[i][j] = in[i][j];
        }
    }

    KeyExpansion(cipherKey, expandedKeys);

    AddRoundKeys(expandedKeys, out, 0);

    //test    
    for(int i = 0; i < STATE_ROWS; i++)
    {
        for(int j = 0; j < STATE_COLUMNS; j++)
        {
            printf("%x", out[j][i]);
        }
    }
    puts("\n");
    //test

    for(k = 1; k < ( NUMBER_ROUNDS - 1 ); k++)
    {
        SubBytes(out);
        ShiftRows(out);
        MixColumns(out);
        AddRoundKeys(expandedKeys, out, k);
    }

    SubBytes(out);
    ShiftRows(out);
    AddRoundKeys(expandedKeys, out, NUMBER_ROUNDS-1);
}
