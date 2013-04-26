#include "aes.h"
#include <stdio.h>

void encrypt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], BYTE cipherKey[KEY_BYTES])
{
    WORD expandedKeys[WORDS_OF_EXPANSION];

    int i, j, k;
    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            out[i][j] = in[i][j];
        }
    }

    KeyExpansion(cipherKey, expandedKeys);
        printf("round[%d].input = ", 0);
      
        for(int i = 0; i < STATE_ROWS; i++)
        {
            for(int j = 0; j < STATE_COLUMNS; j++)
            {
                printf("%x", out[j][i]);
            }
        }       
        puts("\n");

    AddRoundKeys(expandedKeys, out, 0);
        printf("round[%d].output = ", 0);
        for(int i = 0; i < STATE_ROWS; i++)
        {
            for(int j = 0; j < STATE_COLUMNS; j++)
            {
                printf("%x", out[j][i]);
            }
        }       
        puts("\n");
    for(k = 1; k < ( NUMBER_ROUNDS - 1 ); k++)
    {
        printf("round[%d].start = ", k);
        for(int i = 0; i < STATE_ROWS; i++)
        {
            for(int j = 0; j < STATE_COLUMNS; j++)
            {
                printf("%x", out[j][i]);
            }
        }
        puts("\n");

        SubBytes(out);
        ShiftRows(out);
        MixColumns(out);

        printf("round[%d].k_sch = ", k);
        for(int i = 0; i < STATE_ROWS; i++)
        {
            printf("%x", expandedKeys[STATE_COLUMNS*k+i]);
        }
        puts("\n");

        AddRoundKeys(expandedKeys, out, k);
        printf("round[%d].output = ", k);
        for(int i = 0; i < STATE_ROWS; i++)
        {
            for(int j = 0; j < STATE_COLUMNS; j++)
            {
                printf("%x", out[j][i]);
            }
        }       
        puts("\n");
    }

    SubBytes(out);
    ShiftRows(out);
    AddRoundKeys(expandedKeys, out, NUMBER_ROUNDS-1);
        printf("round[%d].output = ", k);
        for(int i = 0; i < STATE_ROWS; i++)
        {
            for(int j = 0; j < STATE_COLUMNS; j++)
            {
                printf("%x", out[j][i]);
            }
        }       
        puts("\n");
}
