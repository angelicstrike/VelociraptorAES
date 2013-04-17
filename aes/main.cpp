#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "matt.cpp"
int main()
{
    unsigned char bytes[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x04, 0x05, 0x06, 0x07},
      {0x08, 0x09, 0x0a, 0x0b},
      {0x0c, 0x0d, 0x0e, 0x0f }};

    unsigned char bytesCheck[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x05, 0x06, 0x07, 0x04},
      {0x0a, 0x0b, 0x08, 0x09},
      {0x0f, 0x0c, 0x0d, 0x0e }};

    AESShiftRows16(*bytes);	

    if (memcmp(*bytes, *bytesCheck, 16) == 0)
	cout << "Success!\n";

}
