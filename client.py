#!/usr/bin/env python3
import pickle
import socket
import threading
import time
import sys

class ConnectionThread(threading.Thread):
    def run(self):
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(('localhost', 65535))

        print(pickle.loads(client.recv(1024)))
        while True:
            message = input("Send message: ")
            try:
                client.send(bytes(message, 'UTF-8'))
            except KeyboardInterrupt:
                client.close()
        client.close()

ConnectionThread().start()
