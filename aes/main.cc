#include "aes.h"
#include "aesTest.h"

int main()
{
    TestSubBytes();
    //TestKeyExpansion();
    TestShiftRows();
    TestMixColumns();
    return 0;
}
