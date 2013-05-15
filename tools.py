def I2H_2D(ints):
    newInts = []
    for row in ints:
        newRow = []
        for value in row:
            newRow.append(hex(value))
        newInts.append(newRow)
    return newInts

def generateKey256(string):
    cipherKey = []
    for i in range(0, 32):
        cipherKey.append(ord(string[i%len(string)]))
    return cipherKey

def generateBlocks128(string):
    blockCount = len(string)/16 + 1
    blocks = []
    for i in range(0, blockCount-1):
        block = []
        for j in range(0, 4):
            row = []
            for k in range(0, 4):
                row.append(ord(string[16*i+4*j+k]))
            block.append(row)
        blocks.append(block)

    if len(string) % 16 != 0:
        remaining = string[16*(blockCount-1): len(string)]
        finalBlock = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
        for i in range(0, len(remaining)):
            finalBlock[i/4][i%4] = ord(remaining[i])
        blocks.append(finalBlock)

    return blocks

def generateString16(blocks):
    string = []
    if len(blocks) == 1:
        for block in blocks:
            for row in block:
                for value in row:
                    string.append(chr(value))

    elif len(blocks) > 1:
        for row in blocks:
            for value in row:
                string.append(chr(value))

    return ''.join(string)
    
