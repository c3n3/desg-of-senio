  #!/usr/bin/env python
  
import socket

TCP_IP = '192.168.50.94'
TCP_PORT = 8090
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
while True:
    msg = input("Message: ")
    if (msg == "q"):
        break
    s.send(bytes(msg, "utf-8"))
    # data = s.recv(BUFFER_SIZE)

s.close()
