#ifndef AES_TEST_H
#define AES_TEST_H

#include "aes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TestSubBytes();
void TestKeyExpansion();
void TestShiftRows();
void TestMixColumns();

void TestInvSubBytes();

#endif
