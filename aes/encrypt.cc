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
    AddRoundKeys(expandedKeys, out, 0);
    
    for(k = 1; k < ( NUMBER_ROUNDS ); k++)
    {
        SubBytes(out);
        ShiftRows(out);
        MixColumns(out);
        AddRoundKeys(expandedKeys, out, k);
    }

    SubBytes(out);
    ShiftRows(out);
    AddRoundKeys(expandedKeys, out, NUMBER_ROUNDS);
}
