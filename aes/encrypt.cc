#include "aes.h"
#include <stdio.h>
#include <string.h>

void encrypt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], BYTE cipherKey[KEY_BYTES])
{
    memcpy(*out, *in, 16);

    WORD expandedKeys[WORDS_OF_EXPANSION];
    KeyExpansion(cipherKey, expandedKeys);

    AddRoundKeys(expandedKeys, out, 0);
    for(int k = 1; k <= NUMBER_ROUNDS-1; k++)
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
