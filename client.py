#!/usr/bin/env python3
import socket
import threading
import sys
import signal
import ctypes
import os

directory = os.getcwd()
pathKellos = directory + '/stringReturnTest2.so'

aes = ctypes.cdll.LoadLibrary(pathKellos)

def callEncrypt(string,key)
    c_stringToEncrypt = ctypes.c_char_p(string)
	c_keyString = ctypes.c_char_p(key)
	foo = aes.EncryptMessage(c_stringToEncrypt,c_keyString)
	returnCopy = ctypes.c_char_p(foo).value
	del(foo)
	aes.FreeCipherString()
	return returnCopy

def callDecrypt(string,key)
    c_stringToDecrypt = ctypes.c_char_p(string)
	c_keyString = ctypes.c_char_p(key)
	foo = aes.decrypt(c_stringToDecrypt,c_keyString)
	returnCopy = ctypes.c_char_p(foo).value
	del(foo)
	hello.FreeCipherString()
	return returnCopy

HOST = sys.argv[1]
PORT = sys.argv[2]
USER = sys.argv[3]

class ConnectionThread(threading.Thread):
    def run(self):
        print("Connection established")
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((HOST, int(PORT)))
        # client.send(bytes(USER + ' connected', 'UTF-8'))
        print("To quit, type /quit.")

        while(True):
            message = input("Send: ")
            received = client.recv(1024)
            print('Received: ' + received.decode('UTF-8'))

            if "/quit" in message:
                break
            else:
                client.send(bytes(message + ' ', 'UTF-8'))
        sys.exit(0)

ConnectionThread().start()
