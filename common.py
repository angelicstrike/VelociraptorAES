from values import *

def subWord(word):

    temp = 0
    subs = [0, 0, 0, 0]
    for i in range(0, 4):
        temp = (word & (0xFF << (8*i))) >> (8*i)
        x = (temp & 0xF0) >> 4
        y = (temp & 0x0F)
        subs[i] = s[x][y]

    return subs[0] | (subs[1] << 8) | (subs[2] << 16) | (subs[3] << 24)

def rotWord(word):

    temp = (word & 0xFF000000) >> (6*4)
    word <<= 8
    word |= (temp & 0x000000FF)

    return word

def keyExpansion(key):
    w = []
    for i in range(0, NUMBER_WORDS_KEY):
        w.append((key[(4*i)+3]) | (key[(4*i)+2] << 8) | (key[(4*i)+1] << 16) | (key[(4*i)] << 24))

    for i in range(NUMBER_WORDS_KEY, (STATE_COLUMNS*(NUMBER_ROUNDS+1))):
        temp = w[i-1]
        if (i % NUMBER_WORDS_KEY == 0):
            temp = subWord(rotWord(temp)) ^ (rcon[i/NUMBER_WORDS_KEY] << 6*4)
        elif (NUMBER_WORDS_KEY > 6) and (i % NUMBER_WORDS_KEY == 4):
            temp = subWord(temp)
        w.append(w[i-NUMBER_WORDS_KEY] ^ temp)

    return w

def addRoundKeys(keys, state, k):
    for i in range(0, STATE_COLUMNS):
        state[0][i] = state[0][i] ^ ((keys[k*STATE_COLUMNS + i] & 0xFF000000 ) >> 24)
        state[1][i] = state[1][i] ^ ((keys[k*STATE_COLUMNS + i] & 0x00FF0000) >> 16)
        state[2][i] = state[2][i] ^ ((keys[k*STATE_COLUMNS + i] & 0x0000FF00) >> 8)
        state[3][i] = state[3][i] ^ (keys[k*STATE_COLUMNS + i] & 0x000000FF)
    return state

def subBytes(state):
    x = 0
    y = 0
    for i in range(0, STATE_COLUMNS):
        for j in range(0, STATE_ROWS):
            x = (state[i][j] & 0xF0) >> 4
            y = (state[i][j] & 0x0F)
            state[i][j] = s[x][y]
    return state

def invSubBytes(state):
    x = 0
    y = 0
    for i in range(0, STATE_ROWS):
        for j in range(0, STATE_COLUMNS):
            x = (state[i][j] & 0xF0) >> 4
            y = (state[i][j] & 0x0F)
            state[i][j] = inv_s[x][y]
 
    return state

def shiftRows(state):
    temp = [0,0,0,0]
    for row in range(1, STATE_ROWS):
        for col in range(0, STATE_COLUMNS):
            temp[col] = state[row][col]
        for col in range(0, STATE_COLUMNS):
            state[row][col] = temp[(col+row)%4]
    return state

def invShiftRows(state):
    temp = [0,0,0,0]
    for row in range(1, STATE_ROWS):
        for col in range(0, STATE_COLUMNS):
            temp[col] = state[row][col]
        for col in range(0, STATE_COLUMNS):
            state[row][col] = temp[(col+(4-row))%4]
    return state
 
def mixColumns(state):
    modulo = (1<<8) + (1<<4) + (1<<3) + (1<<1) + 1

    temp = [0,0,0,0]
    for col in range(0, STATE_COLUMNS):
        for row in range(0, STATE_ROWS):
            temp[row] = state[row][col]
        for row in range(0, STATE_ROWS):
            result = 0
            for i in range(0, STATE_ROWS):
                if ColMixer[row][i] & 1:
                    result ^= temp[i]
                if ColMixer[row][i] & 2:
                    result ^= (temp[i]<<1)
            if (result >= 1<<12):
                result ^= (modulo<<4)
            if (result >= 1<<11):
                result ^= (modulo<<3)
            if (result >= 1<<10):
                result ^= (modulo<<2)
            if (result >= 1<<9):
                result ^= (modulo<<1)
            if (result >= 1<<8):
                result ^= (modulo)

            state[row][col] = result

    return state

def invMixColumns(state):
    modulo = (1<<8) + (1<<4) + (1<<3) + (1<<1) + 1

    temp = [0,0,0,0]
    for col in range(0, STATE_COLUMNS):
        for row in range(0, STATE_ROWS):
            temp[row] = state[row][col]
        for row in range(0, STATE_ROWS):
            result = 0
            for i in range(0, STATE_ROWS):
                if InvColMixer[row][i] & 1:
                    result ^= temp[i]
                if InvColMixer[row][i] & 2:
                    result ^= (temp[i]<<1)
                if InvColMixer[row][i]&4:
                    result ^= temp[i]<<2;
                if InvColMixer[row][i]&8:
                    result ^= temp[i]<<3;
 
            if (result >= 1<<12):
                result ^= (modulo<<4)
            if (result >= 1<<11):
                result ^= (modulo<<3)
            if (result >= 1<<10):
                result ^= (modulo<<2)
            if (result >= 1<<9):
                result ^= (modulo<<1)
            if (result >= 1<<8):
                result ^= (modulo)

            state[row][col] = result

    return state
