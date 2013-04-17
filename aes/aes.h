#ifndef AES_H
#define AES_H

#define STATE_ROWS 4
#define STATE_COLUMNS 6
#define KEY_BYTES 32
#define BLOCK_SIZE 16
#define NUMBER_ROUNDS 14

unsigned int SubBytes(unsigned int key, unsigned int[STATE_ROWS][STATE_COLUMNS] state);//need state and key and what else?

unsigned int ShiftRows(unsigned int key, unsigned int[STATE_ROWS][STATE_COLUMNS] state);

unsigned int MixColumns(unsigned int key, unsigned int[STATE_ROWS][STATE_COLUMNS] state);

//Generates round keys from the main key using Rijndael's key scheduler and the main key
unsigned int AddRoundKeys(unsigned int key, unsigned int[STATE_ROWS][STATE_COLUMNS] state);

#endif
