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
#endif
