#ifndef COMMON_C
#define COMMON_C

#include "aes.h"

void SubBytes(unsigned int key, BYTE **state)//your issue
{
        
}

void ShiftRows(BYTE** state)//your issue, this is already done, i just have to move it to here :P
{

}

void MixColumns(BYTE** state)//my issue
{
    int i, j, k;
    for(i = 0; i < STATE_COLUMNS; i++)
    {
        for(j = 0; j < STATE_ROWS; j++)
        {
        }
    }
}

void AddRoundKeys(unsigned int key, BYTE** state)//my issue
{

}

#endif
