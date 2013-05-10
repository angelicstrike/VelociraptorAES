#include "aes.h"

BYTE** encryptMessage(const char* message, BYTE cipherKey[KEY_BYTES])
{
    int i,j;
    int k = 0;
    BYTE in[STATE_ROWS][STATE_COLUMNS];
    BYTE out[STATE_ROWS][STATE_COLUMNS];

    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            if(message)
            {
                in[j][i] = message[k];
            }
            else
            {
                in[j][i] = 0x00;
            }
            k++;
        }

    }

    encrypt(in, out, cipherKey);

}
