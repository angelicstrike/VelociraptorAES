#include "aesTest.h"

void TestSubBytes()
{
    BYTE testState[4][4] = {{0xF0, 0xc5, 0x56, 0x99},
                            {0x00, 0xFF, 0x9C, 0x53},
                            {0x66, 0x29, 0xAD, 0xCC},
                            {0x45, 0xFA, 0xFD, 0x01}};

    BYTE SubBytesState[4][4] = {{0x8C, 0xA6, 0xB1, 0xEE},
                                {0x63, 0x16, 0xDE, 0xED},
                                {0x33, 0xA5, 0x95, 0x4B},
                                {0x6E, 0x2D, 0x54, 0x7C}};
    SubBytes(testState);
    int i,j;
    for(i = 0; i < STATE_COLUMNS; i++)
    {
        for(j = 0; j < STATE_ROWS; j++)
        {
            if(testState[i][j] != SubBytesState[i][j])
            {
                puts("Incorrect funtionality in SubBytes");
                return;
            }
        }
    }

    puts("SubBytes has passed the test");
}

void TestKeyExpansion()
{
    unsigned int testExpansion[60];

    BYTE testKey[32] = 
    {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    };

    unsigned int testVector[60] = 
    {
        0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07,
        0x3b6108d7, 0x2d9810a3, 0x0914dff4, 0x9ba35411, 0x8e6925af, 
        0xa51a8b5f, 0x2067fcde, 0xa8b09c1a, 0x93d194cd, 0xbe49846e, 
        0xb75d5b9a, 0xd59aecb8, 0x5bf3c917, 0xfee94248, 0xde8ebe96, 
        0xb5a9328a, 0x2678a647, 0x98312229, 0x2f6c79b3, 0x812c81ad, 
        0xdadf48ba, 0x24360af2, 0xfab8b464, 0x98c5bfc9, 0xbebd198e, 
        0x268c3ba7, 0x09e04214, 0x68007bac, 0xb2df3316, 0x96e939e4, 
        0x6c518d80, 0xc814e204, 0x76a9fb8a, 0x5025c02d, 0x59c58239, 
        0xde136967, 0x6ccc5a71, 0xfa256395, 0x9674ee15, 0x5886ca5d, 
        0x2e2f31d7, 0x7e0af1fa, 0x27cf73c3, 0x749c47ab, 0x18501dda, 
        0xe2757e4f, 0x7401905a, 0xcafaaae3, 0xe4d59b34, 0x9adf6ace, 
        0xbd10190d, 0xfe4890d1, 0xe6188d0b, 0x046df344, 0x706c631e
    };


    KeyExpansion(testKey, testExpansion);
    int i;

    for(i = 0; i < 60; i++)
    {
        if(testExpansion[i] != testVector[i])
        {
            puts("KeyExpansion has failed. We do not reward failure.");
            return;
        }
    }

    puts("KeyExpansion has passed the test.");
}

void TestShiftRows()
{
    BYTE bytes[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x04, 0x05, 0x06, 0x07},
      {0x08, 0x09, 0x0a, 0x0b},
      {0x0c, 0x0d, 0x0e, 0x0f} };

    BYTE ShiftCheck[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x05, 0x06, 0x07, 0x04},
      {0x0a, 0x0b, 0x08, 0x09},
      {0x0f, 0x0c, 0x0d, 0x0e} };

    BYTE unShiftCheck[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x04, 0x05, 0x06, 0x07},
      {0x08, 0x09, 0x0a, 0x0b},
      {0x0c, 0x0d, 0x0e, 0x0f} };


    ShiftRows(bytes);	
    if (memcmp(*bytes, *ShiftCheck, 16) == 0)
	    printf("Shift Rows Success!\n");
    else
        printf("Shift Rows Failure. Inverse Should Now Fail.\n");

    InvShiftRows(bytes);
    if (memcmp(*bytes, *unShiftCheck, 16) == 0)
        printf("Inverse Shift Rows success.\n");
    else
        printf("Inverse Shift Rows Failure.\n");

}

void TestMixColumns()
{
    BYTE bytes[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x05, 0x06, 0x07, 0x04},
      {0x0a, 0x0b, 0x08, 0x09},
      {0x0f, 0x0c, 0x0d, 0x0e} };

    BYTE MixCheck[8] =
    {(0x00<<1)^(0x05<<1)^0x05^0x0a^0x0f, 
     (0x01<<1)^(0x06<<1)^0x06^0x0b^0x0c,
     (0x02<<1)^(0x07<<1)^0x07^0x08^0x0d,
     (0x03<<1)^(0x04<<1)^0x04^0x09^0x0e,
     0x00^(0x05<<1)^(0x0a<<1)^0x0a^0x0f,
     0x01^(0x06<<1)^(0x0b<<1)^0x0b^0x0c,
     0x02^(0x07<<1)^(0x08<<1)^0x08^0x0d,
     0x03^(0x04<<1)^(0x09<<1)^0x09^0x0e
     };

    BYTE unMixCheck[4][4] =
    { {0x00, 0x01, 0x02, 0x03},
      {0x05, 0x06, 0x07, 0x04},
      {0x0a, 0x0b, 0x08, 0x09},
      {0x0f, 0x0c, 0x0d, 0x0e} };

    MixColumns(bytes);
    if (memcmp(*bytes, MixCheck, 8) == 0)
        printf("Mix Columns Success! (Two Row Test)\n");
    else
        printf("Mix Columns Failure. Inverse should now fail too.\n");

    InvMixColumns(bytes);
    if (memcmp(*bytes, *unMixCheck, 16) == 0)
        printf("Inverse Mix Columns Success!\n");
    else
        printf("Inverse Mix Columns Failure.\n");
}

//since SubBytes and InvSubBytes are Inverses of each other,
//they *should* cancel each other out and leave the state 
//matrix in it's original form
void TestInvSubBytes()
{
    BYTE testState[4][4] = {{0xF0, 0xc5, 0x56, 0x99},
                            {0x00, 0xFF, 0x9C, 0x53},
                            {0x66, 0x29, 0xAD, 0xCC},
                            {0x45, 0xFA, 0xFD, 0x01}};

    /*BYTE SubBytesState[4][4] = {{0x8C, 0xA6, 0xB1, 0xEE},i
                                {0x63, 0x16, 0xDE, 0xED},
                                {0x33, 0xA5, 0x95, 0x4B},
                                {0x6E, 0x2D, 0x54, 0x7C}};
    */
    BYTE InvSubBytesState[4][4] = {{0x17, 0x07, 0xB9, 0xF9}, 
                                   {0x52, 0x7D, 0x1C, 0x50}, 
                                   {0xD3, 0x4C, 0x18, 0x27}, 
                                   {0x68, 0x14, 0x21, 0x09}};

    SubBytes(testState);
    InvSubBytes(testState);
    InvSubBytes(testState);
    

    int i, j;
    for(i = 0; i < STATE_ROWS; i++)
    {
        for(j = 0; j < STATE_COLUMNS; j++)
        {
            if(testState[i][j] != InvSubBytesState[i][j])
            {
                printf("InvSubBytes has failed me for the last time. Executing it as an example to the others\n");
                exit(1);
            }
        }
    }

    printf("InvSubBytes has passed the test.\n");

}

void TestEncryption()
{
    char* plainText = "00112233445566778899aabbccddeeff";
    char* cipherKey = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    char* cipherText = "8ea2b7ca516745bfeafc49904b496089";

    char* pos = plainText;

    BYTE state[STATE_ROWS][STATE_COLUMNS];
    BYTE out[STATE_ROWS][STATE_COLUMNS];
    BYTE cipherKeyArray[KEY_BYTES];


    for(int i = 0; i < STATE_ROWS; i++)
    {
        for(int j = 0; j < STATE_COLUMNS; j++)
        {
            sscanf(pos, "%02hhx", &state[j][i]);
            pos += 2;
        }
    }

    pos = cipherKey;
    for(int k = 0; k < KEY_BYTES; k++)
    {
        sscanf(pos, "%02hhx", &cipherKeyArray[k]);
        pos += 2;
    }

    encrypt(state, out, cipherKeyArray);

    for(int i = 0; i < STATE_ROWS; i++)
    {
        for(int j = 0; j < STATE_COLUMNS; j++)
        {
            printf("%x", out[j][i]);
        }
    }

}

void TestDecrypt()
{

}
