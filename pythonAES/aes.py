from common import *
from tools import *

# Takes an input string and key string, outputs encrypted string
def EncryptAES256(ptString, key):
    cipherKey = generateKey256(key)
    plaintext = generateBlocks128(ptString)

    cipherText = []
    for i in range(0, len(plaintext)):
        cipherText.append([[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]])

    for i in range(0, len(plaintext)):
        encrypt(plaintext[i], cipherText[i], cipherKey)

    ctString = ""
    for i in range(0, len(plaintext)):
        ctString += generateString16(cipherText[i])

    return ctString


def DecryptAES256(ctString, key):
    cipherKey = generateKey256(key)
    cipherText = generateBlocks128(ctString)

    plaintext = []
    for i in range(0, len(cipherText)):
        plaintext.append([[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]])

    for i in range(0, len(cipherText)):
        decrypt(cipherText[i], plaintext[i], cipherKey)

    ptString = ""
    for i in range(0, len(cipherText)):
        ptString += generateString16(plaintext[i])

    print ptString
    return ptString

def encrypt(pt, ct, key):

    expandedKeys = keyExpansion(key)

    for i in range(0, STATE_ROWS):
        for j in range(0, STATE_COLUMNS):
            ct[i][j] = pt[i][j]

    ct = addRoundKeys(expandedKeys, ct, 0)
    for k in range(1, NUMBER_ROUNDS):
        ct = subBytes(ct)
        ct = shiftRows(ct)
        ct = mixColumns(ct)
        ct = addRoundKeys(expandedKeys, ct, k)

    ct = subBytes(ct)
    ct = shiftRows(ct)
    ct = addRoundKeys(expandedKeys, ct, NUMBER_ROUNDS)

def decrypt(ct, pt, key):

    expandedKeys = keyExpansion(key)

    for i in range(0, STATE_ROWS):
        for j in range(0, STATE_COLUMNS):
            pt[i][j] = ct[i][j]

    pt = addRoundKeys(expandedKeys, pt, NUMBER_ROUNDS)
    pt = invShiftRows(pt)
    pt = invSubBytes(pt)
    for k in range(NUMBER_ROUNDS-1, 0, -1):
        pt = addRoundKeys(expandedKeys, pt, k)
        pt = invMixColumns(pt)
        pt = invShiftRows(pt)
        pt = invSubBytes(pt)

    pt = addRoundKeys(expandedKeys, pt, 0)

