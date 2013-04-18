#include "aes.h"
#include "databoxes.h"
#include "matt.h"

// bytePtr needs to be the pointer to 16 bytes of data, this can be a 1-d or 2-d array
void AESShiftRows(BYTE *bytePtr)
{
    // loops through rows. row 0 offset is 0 so skip it
    int temp[4];
    for (int row = 1; row < 4; row++)
    {
        // Stores the values temporarily
        for (int col = 0; col < 4; col++)
            temp[col] = bytePtr[row*4+col];

        // Withdraws the values in the offsetted locations
        for (int col = 0; col < 4; col++)
            bytePtr[row*4 + col] = temp[(col+row)%4];
    }
}


// This multiplies and xors a 4-byte vector based on the corresponding multipliers
int mixColumnsMult(BYTE *values, BYTE *mult)
{
    int returnVal = 0;
    for (int i = 0; i < 4; i++)
    {
        if (mult[i] == 1)
            returnVal ^= values[i];
        else if (mult[i] == 2)
            returnVal ^= values[i] << 1;
        else if (mult[i] == 3)
            returnVal ^= (values[i] << 1) ^ values[i];
        else
        {
            cout << "Invalid Multiplier given for mix columns.\n";
            return -1;
        }
    }
    return returnVal;
}

// This performs the mix columns operation. 
void AESMixColumns(BYTE *bytePtr)
{
    BYTE temp[4];
    int mult[4];

    // Runs through each column
    for (int col = 0; col < 4; col++)
    {
        // Stores the column values and multipliers for the given column
        for (int row = 0; row < 4; row++)
            temp[row] = bytePtr[row*4+col];

        // Performs operation now that the columns are stored
        for (int row = 0; row < 4; row++)
            bytePtr[col+row*4] = mixColumnsMult(temp, colMixer[row]);
    }
}
