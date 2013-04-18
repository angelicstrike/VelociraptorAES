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

    unsigned char shiftCheck[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x05, 0x06, 0x07, 0x04},
      {0x0a, 0x0b, 0x08, 0x09},
      {0x0f, 0x0c, 0x0d, 0x0e }};

    unsigned char mixCheck[8] =
    {(0x00<<1)^(0x05<<1)^0x05^0x0a^0x0f, 
     (0x01<<1)^(0x06<<1)^0x06^0x0b^0x0c,
     (0x02<<1)^(0x07<<1)^0x07^0x08^0x0d,
     (0x03<<1)^(0x04<<1)^0x04^0x09^0x0e,
     0x00^(0x05<<1)^(0x0a<<1)^0x0a^0x0f,
     0x01^(0x06<<1)^(0x0b<<1)^0x0b^0x0c,
     0x02^(0x07<<1)^(0x08<<1)^0x08^0x0d,
     0x03^(0x04<<1)^(0x09<<1)^0x09^0x0e
     };

    AESShiftRows(*bytes);	
    if (memcmp(*bytes, *shiftCheck, 16) == 0)
	    cout << "Shift Rows Success!\n";
    else
        cout << "Shift Rows Failure.\nNo further tests should succeed now\n";

    AESMixColumns(*bytes);
    if (memcmp(*bytes, mixCheck, 8) == 0)
        cout << "Mix Columns Success! (Two Row Test)\n";
    else
        cout << "Mix Columns Failure.\nNo further tests should succeed now\n";
}