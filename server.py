#!/usr/bin/env python3
import socket
import threading
import signal
import sys

PORT = sys.argv[1]

class ClientThread(threading.Thread):
    def __init__(self, channel, details):
        self.channel = channel
        self.details = details
        threading.Thread.__init__(self)

    def run(self):
        print('Received connection'), self.details[0]
        # self.channel.send(bytes("Connection established", 'UTF-8'))

        while(True):
            try:
                send = input("Send: ")
                self.channel.send(bytes(send + ' ', 'UTF-8'))
                message = self.channel.recv(1024)
                if "/quit" in send:
                    break
                else:
                    print('Received: '+ message.decode('UTF-8'))
            except (BrokenPipeError, ConnectionResetError):
                sys.exit(0)
        #self.channel.close()
        sys.exit(0)

signal.signal(signal.SIGINT, signal.SIG_IGN)

server = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
server.bind(('', int(PORT)))
server.listen(5)

while True:
    channel, details = server.accept()
    ClientThread(channel, details).start()
