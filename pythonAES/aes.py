from common import *
from tools import *

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

