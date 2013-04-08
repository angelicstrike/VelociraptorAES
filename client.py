#!/usr/bin/python
import pickle
import socket
import threading
import time

class ConnectionThread(threading.Thread):
    def run(self):
	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect(('localhost', 8000))

	print pickle.loads(client.recv(1024))

	for x in xrange(5):
	    client.send("Hello, test #" +str(x)+ "\n")
	    time.sleep(1)

	client.close()

ConnectionThread().start()
