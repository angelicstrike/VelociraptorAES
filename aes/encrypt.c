#ifndef AES_ENCRYPT_C
#define AES_ENCRYPT_C

#include "aes.h"
#include "databoxes.h"

//since we don't have a way to generate a 256 bit key yet, or share it, I'm just
//putting a hardcoded key in here for now -- angelicstrike

void encryt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS])
{
    unsigned int expandedKeys[WORDS_OF_EXPANSION];
    unsigned int cipherKey[NUMBER_WORDS_KEY] = 
    {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    };

    int i, j, k;
    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            out[i][j] = in[i][j];
        }
    }

    KeyExpansion(key, expandedKeys);

    AddRoundKeys(expandedKeys, out, 0);

    for(k = 1; k < ( NUMBER_ROUNDS - 1 ); k++)
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

#endif
