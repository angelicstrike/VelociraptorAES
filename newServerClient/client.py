import socket
import sys
import select
import re
from communication import send, receive, jumble
from aes import EncryptAES256, DecryptAES256

BUFSIZ = 1024

class ChatClient(object):
    """ A simple command line chat client using select """

    def __init__(self, name, host, port, key):
        self.name = name
        self.flag = False
        self.port = int(port)
        self.host = host
        self.key = key
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((host, self.port))
            print 'Connected to chat server@%d' % self.port
            # Send my name...
            send(self.sock,'NAME: ' + self.name) 
            data = receive(self.sock)
            # Contains client address, set it
            addr = data.split('CLIENT: ')[1]
            self.prompt = '@'.join((self.name, addr)) + '> '
        except socket.error, e:
            print 'Could not connect to chat server @%d' % self.port
            sys.exit(1)

    def cmdloop(self):

        while not self.flag:
            try:
                sys.stdout.write(self.prompt)
                sys.stdout.flush()

                inputready, outputready,exceptrdy = select.select([0, self.sock], [],[])
                
                for i in inputready:
                    if i == 0:
                        data = sys.stdin.readline().strip()
                        if data:
                            encryptMsg =  EncryptAES256(data, self.key)
                            send(self.sock, encryptMsg)
                    elif i == self.sock:
                        data = receive(self.sock)
                        if re.search('>>',data) != None:
                            fromC = data.split('>> ')[0]
                            msg = data.split('>> ')[1]
                            decryptMsg = DecryptAES256(msg, self.key)
                            data = fromC + '>> ' + decryptMsg
                        if not data:
                            print 'Shutting down.'
                            self.flag = True
                            break
                        else:
                            sys.stdout.write(data + '\n')
                            sys.stdout.flush()
                            
            except KeyboardInterrupt:
                print 'Interrupted.'
                self.sock.close()
                break
            
            
if __name__ == "__main__":
    import sys

    if len(sys.argv)<4:
        sys.exit('Usage: %s chatid host portno key' % sys.argv[0])
        
    client = ChatClient(sys.argv[1],sys.argv[2], int(sys.argv[3]), sys.argv[4])
    client.cmdloop()
