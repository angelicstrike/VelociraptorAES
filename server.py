#!/usr/bin/env python3
import pickle
import socket
import threading
import signal

welcomeMessage = pickle.dumps("Connection established")

class ClientThread(threading.Thread):
    def __init__(self, channel, details):
        self.channel = channel
        self.details = details
        threading.Thread.__init__(self)

    def run(self):
        print('Received connection:'), self.details[0]
        self.channel.send(welcomeMessage)
        while(True):
            message = self.channel.recv(1024)
            if 'quit' in message.decode('UTF-8'):
                break;
            else:
                print(message.decode('UTF-8'))
        #self.channel.close()
        print('Closed connection:'), self.details[0]

signal.signal(signal.SIGINT, signal.SIG_IGN)

server = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
server.bind(( '', 65535))
server.listen(5)

while True:
    try:
        channel, details = server.accept()
        ClientThread(channel, details).start()
    except KeyboardInterrupt:
        break
