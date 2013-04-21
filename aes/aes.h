#ifndef AES_H
#define AES_H

#define STATE_ROWS 4
#define STATE_COLUMNS 4
#define KEY_BYTES 32
#define NUMBER_WORDS_KEY 8
#define NUMBER_ROUNDS 14
#define WORDS_OF_EXPANSION 240
typedef unsigned char BYTE;
typedef unsigned int WORD;


void SubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void ShiftRows(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void MixColumns(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void AddRoundKeys(unsigned int key[WORDS_OF_EXPANSION], BYTE** state);

void KeyExpansion(unsigned int key[KEY_BYTES], unsigned int word[WORDS_OF_EXPANSION], int round);
unsigned int SubWord(unsigned int word);
unsigned int RotWord(unsigned int word);

void InvSubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);


#endif
