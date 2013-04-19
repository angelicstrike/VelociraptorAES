#ifndef AES_H
#define AES_H

#define STATE_ROWS 4
#define STATE_COLUMNS 4
#define KEY_BYTES 32
#define NUMBER_ROUNDS 14
typedef unsigned char BYTE;

void SubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);

void ShiftRows(BYTE **state);

void MixColumns(BYTE **state);

/*Generates round keys from the main key using Rijndael's key scheduler and the main key*/
void AddRoundKeys(unsigned int key, BYTE** state);

#endif
