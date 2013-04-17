#ifndef AES_H
#define AES_H

unsigned int SubBytes(unsigned int key, unsigned int[4][6] state);//need state and key and what else?

unsigned int ShiftRows(unsigned int key, unsigned int[4][6] state);

unsigned int MixColumns(unsigned int key, unsigned int[4][6] state);

//Generates round keys from the main key using Rijndael's key scheduler and the main key
unsigned int AddRoundKeys(unsigned int key, unsigned int[4][6] state);

#endif
