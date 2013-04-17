#!/usr/bin/python
import pickle
import socket
import threading
import time
import sys

class ConnectionThread(threading.Thread):
    def run(self):
	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect(('localhost', 8000))

	print pickle.loads(client.recv(1024))
	
	while True:
	    message = raw_input("Send message: ")
	    client.send(message)
	    client.close()
	#for x in xrange(100):
	    #try:
		#client.send(sys.argv[x])
	    #except IndexError:
	#	break

ConnectionThread().start()
