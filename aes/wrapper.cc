#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BYTE* returnString;

BYTE* EncryptMessage(const char* message, BYTE cipherKey[KEY_BYTES])
{
    int i,j;
    int k = 0;
    int l = 0;
    BYTE in[STATE_ROWS][STATE_COLUMNS];
    BYTE out[STATE_ROWS][STATE_COLUMNS];


    returnString = (BYTE*)malloc( sizeof(BYTE) * (unsigned)strlen(message));

    if(returnString == NULL)
        exit(1);

    returnString = 0;//put in an empty string so it will have something in it for now
    //while((message + k) != NULL)
    {

        for(i = 0; i < STATE_ROWS; i++)
        {
            for(j = 0; j < STATE_COLUMNS; j++)
            {
                if((message+k) != NULL)
                {
                    in[j][i] = *(message + k);
                }
                else
                {
                    in[j][i] = 0x00;
                }
                k++;

            }
        }

        encrypt(in, out, cipherKey);

        for(i = 0; i < STATE_ROWS; i++)
        {
            for(j = 0; j < STATE_COLUMNS; j++)
            {
                if((returnString+l) != NULL)
                {
                    //*(returnString + l) = out[j][i]; //I hate this line so much
                }

                l++;
            }
        }
    }

    return returnString;
}

void FreeCipherString()
{
    free(returnString);
}
