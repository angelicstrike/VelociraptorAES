#!/usr/bin/python
import pickle
import socket
import threading

randomList = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
#chosenList = pickle.dumps(randomList)
chosenList = pickle.dumps("Connection established")

class ClientThread(threading.Thread):
    def __init__(self, channel, details):
	self.channel = channel
	self.details = details
	threading.Thread.__init__(self)

    def run(self):
	print 'Received connection:', self.details [0]
	self.channel.send(chosenList)
	while True:
	    print self.channel.recv(1024)
	self.channel.close()
	print 'Closed connection:', self.details [0]

server = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
server.bind(( '', 8000))
server.listen(5)

while True:
    channel, details = server.accept()
    ClientThread(channel, details).start()
