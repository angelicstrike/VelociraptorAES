#ifndef AES_TEST_H
#define AES_TEST_H

#include <stdio.h>
#include "aes.h"

void TestSubBytes()
{
    BYTE testState[4][4] = {{0xF0, 0xc5, 0x56, 0x99},
                            {0x00, 0xFF, 0x9C, 0x53},
                            {0x66, 0x29, 0xAD, 0xCC},
                            {0x45, 0xFA, 0xFD, 0x01}};

    BYTE SubBytesState[4][4] = {{0x8C, 0xA6, 0xB1, 0xEE},
                                {0x63, 0x16, 0xDE, 0xED},
                                {0x33, 0xA5, 0x95, 0x4B},
                                {0x6E, 0x2D, 0x54, 0x7C}};
    SubBytes(testState);
    int i,j;
    for(i = 0; i < STATE_COLUMNS; i++)
    {
        for(j = 0; j < STATE_ROWS; j++)
        {
            if(testState[i][j] != SubBytesState[i][j])
            {
                puts("Incorrect funtionality in SubBytes");
                return;
            }
        }
    }

    puts("SubBytes has passed the test");
}

#endif
