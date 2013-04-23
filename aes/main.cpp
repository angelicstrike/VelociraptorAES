#include "aesTest.h"

int main()
{
    TestSubBytes();
    TestKeyExpansion();
    TestShiftRows();
    TestMixColumns();
    TestInvSubBytes();

    return 0;
}
