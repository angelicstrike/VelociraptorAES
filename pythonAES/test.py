from tools import *
from aes   import *

plainText   = [
  [0x00, 0x44, 0x88, 0xCC], [0x11, 0x55, 0x99, 0xDD], [0x22, 0x66, 0xaa, 0xEE], [0x33, 0x77, 0xBB, 0xFF]
];

encrypted = [
  [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]
]

decrypted = [
  [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]
]

cipherKey   = [
0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
]

cipherAnswer = [ 
  0x8e, 0xa2, 0xb7, 0xca,
  0x51, 0x67, 0x45, 0xbf,
  0xea, 0xfc, 0x49, 0x90,
  0x4b, 0x49, 0x60, 0x89 
];

#print plainText
#print subBytes(plainText)
#print invSubBytes(plainText)

encrypt(plainText, encrypted, cipherKey)
decrypt(encrypted, decrypted, cipherKey)

plainhex  = I2H_2D(plainText)
encryphex = I2H_2D(encrypted)
decryphex = I2H_2D(decrypted)

#print plainhex
#print encryphex
#print decryphex

original = "bear!"
key = "kitties"
print original
encrypted = EncryptAES256(original, key);
print encrypted
decrypted = DecryptAES256(encrypted, key)
print decrypted

#print generateBlocks128("WHAT ARE YOU DOING OMG THIS IS CRAZY WHOA LOL GO")
#print generateBlocks128("WHAT ARE YOU DOING OMG THIS IS CRAZY WHOA LOL GOO")
#print generateString16(generateBlocks128("WHAT ARE YOU DOING OMG THIS IS CRAZY WHOA LOL GOO"))
