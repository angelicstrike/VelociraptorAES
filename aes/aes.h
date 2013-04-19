#ifndef AES_H
#define AES_H

#define STATE_ROWS 4
#define STATE_COLUMNS 4
#define KEY_BYTES 32
#define NUMBER_WORDS_KEY 8
#define NUMBER_ROUNDS 14
typedef unsigned char BYTE;

/*
 * For this, a word is defined as 32 bits (4 bytes)
 */


void SubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void ShiftRows(BYTE **state);
void MixColumns(BYTE **state);
void AddRoundKeys(unsigned int key, BYTE** state);

/*Nk's value:
 * AES-128 --> 4
 * AES-192 --> 6
 * AES-256 --> 8
*/
void KeyExpansion(unsigned int key, unsigned int word);
unsigned int SubWord(unsigned int word);
unsigned int RotWord(unsigned int word);

#endif
