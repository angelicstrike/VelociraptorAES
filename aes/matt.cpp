#include "aes.h"
#include "databoxes.h"
#include "matt.h"

//bytePtr needs to be a pointer to a pointer for a 2D array (like the state matrix we need), so **bytePtr
void AESShiftRows16(BYTE *bytePtr)
{
    // Each row needs to shift left by the corresponding values
    int offsets[4] = {0, 1, 2, 3};//This is superfluous, you can use
    int temp[4];

    // loops through rows. row 0 offset is 0 so skip it
    for (int row = 1; row < 4; row++)
    {
	// Stores the values temporarily
	for (int col = 0; col < 4; col++)
	    temp[col] = bytePtr[row*4+col];

	// Withdraws the values in the offsetted locations
	int offset = offsets[row];
	for (int col = 0; col < 4; col++)
	    bytePtr[row*4 + col] = temp[(col+offset)%4];
    }
}

void AESMixColumns(BYTE *bytePtr)
{
}
