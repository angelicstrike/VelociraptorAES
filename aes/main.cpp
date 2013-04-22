#include "common.cc"
#include "aesTest.cc"

int main()
{
    TestSubBytes();
    TestKeyExpansion();
    TestShiftRows();
    TestMixColumns();
    return 0;
}
