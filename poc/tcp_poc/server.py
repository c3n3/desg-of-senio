#!/usr/bin/env python
from time import sleep
import socket


TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

def watch_dog(s):
    try:
        s.send(b'w')
        return True
    except Exception:
        return False

conn, addr = s.accept()
print ('Connection address:', addr)
while 1:
    data = conn.recv(BUFFER_SIZE)
    if (not watch_dog(s)):
        print("Socket has been closed\n");
    if (data == b''):
        sleep(0.1)
        continue
    print ("received data:", data)
    conn.send(data)  # echo
conn.close()

