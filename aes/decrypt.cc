#include "aes.h"
#include <stdio.h>
#include <string.h>

void decrypt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], BYTE cipherKey[KEY_BYTES])
{
    memcpy(*out, *in, 16);

    WORD expandedKeys[WORDS_OF_EXPANSION];
    KeyExpansion(cipherKey, expandedKeys);
    
    AddRoundKeys(expandedKeys, out, NUMBER_ROUNDS);
    InvShiftRows(out);
    InvSubBytes(out);
    for(int k = NUMBER_ROUNDS-1; k >= 1; k--)
    {
        AddRoundKeys(expandedKeys, out, k);
        InvMixColumns(out);
        InvShiftRows(out);
        InvSubBytes(out);
    }
    AddRoundKeys(expandedKeys, out, 0);
}
