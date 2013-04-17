#ifndef AES_TEST_H
#define AES_TEST_H

#include "aes.h"
#include "matt.h"


void testShift()
{
    unsigned char testArray[4][4] = {{1,2,3,4},
                                     {5,6,7,8},
                                     {9,10,11,12},
                                     {13,14,15,16}};
    AESShiftRows16(testArray);
}

#endif
