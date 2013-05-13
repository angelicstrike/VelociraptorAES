import cPickle
import socket
import struct
import hashlib
from Crypto.Cipher import AES

#marshall = cPickle.dumps
#unmarshall = cPickle.loads

def send(channel, args):
    buf = args
    value = socket.htonl(len(buf))
    size = struct.pack("L",value)
    channel.send(size)
    channel.send(buf)

def receive(channel):

    size = struct.calcsize("L")
    size = channel.recv(size)
    try:
        size = socket.ntohl(struct.unpack("L", size)[0])
    except struct.error, e:
        return ''
    
    buf = ""

    while len(buf) < size:
        buf = channel.recv(size - len(buf))

    return buf 

def jumble(thingToJumble, otherThing):
	ret = '@' + thingToJumble
	return ret

def unJumble(thingToUnjumble, otherThing):
	ret = thingToUnjumble.lstrip('@')
	return ret

def encrypt(string, key):
	realKey = hashlib.sha256(key).digest()
	mode = AES.MODE_CBC
	encryptor = AES.new(realKey, mode)
	ciphertext = encryptor.encrypt(string)
	return ciphertext

def decrypt(string, key):
	realKey = hashlib.sha256(key).digest()
	mode = AES.MODE_CBC
	decryptor = AES.new(realKey, mode)
	realText = decryptor.decrypt(string)
	return realText
