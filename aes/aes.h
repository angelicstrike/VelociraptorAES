#ifndef AES_H
#define AES_H

#define STATE_ROWS 4
#define STATE_COLUMNS 4
#define KEY_BYTES 32
#define NUMBER_WORDS_KEY 8
#define NUMBER_ROUNDS 14
#define WORDS_OF_EXPANSION 60
typedef unsigned char BYTE;
typedef unsigned int WORD;


void SubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void ShiftRows(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void MixColumns(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void AddRoundKeys(WORD key[WORDS_OF_EXPANSION], BYTE state[STATE_ROWS][STATE_COLUMNS], int round);

void KeyExpansion(BYTE key[KEY_BYTES], WORD w[WORDS_OF_EXPANSION]);
unsigned int SubWord(WORD word);
unsigned int RotWord(WORD word);

void InvShiftRows(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void InvMixColumns(BYTE state[STATE_ROWS][STATE_COLUMNS]);
void InvSubBytes(BYTE state[STATE_ROWS][STATE_COLUMNS]);

void encrypt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], BYTE cipherKey[KEY_BYTES]);
void decrypt(BYTE in[STATE_ROWS][STATE_COLUMNS], BYTE out[STATE_ROWS][STATE_COLUMNS], BYTE cipherKey[KEY_BYTES]);

void printState(BYTE state[STATE_ROWS][STATE_COLUMNS]);

#endif
