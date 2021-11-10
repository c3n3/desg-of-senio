import socket
from threading import Thread
from time import sleep

class Connection():
    def __init__(self, client, addr):
        self.client = client
        self.addr = addr

    def receive(self, size):
        try:
            data = self.client.recv(size)
            return data.decode('utf-8')
        except BlockingIOError:
            return ""

    def send(self, data):
        try:
            data = bytes(data, 'utf-8')
            sent = self.client.send(data)
            if (sent != len(data)):
                print("Not all data sent")
        except BlockingIOError:
            print("Cannot send data")

class Commnunication():
    def __init__(self, ip = '0.0.0.0', port = 8090):
        self.ip = ip
        self.port = port
        self.socket = socket.socket()
        self.thread = Thread(target=self)
        self.connections = []
        self.running = False
        self.threadDelay = 0.1

    def __call__(self, *args, **kwds):
        self.run()

    def startServer(self):
        self.socket.bind((self.ip, self.port))
        self.socket.listen(0)
        print("Starting thread")
        self.running = True
        self.thread.start()

    def run(self):
        print("Running connection loop")
        self.socket.setblocking(0)
        while (self.running):
            try:
                client, addr = self.socket.accept()
                client.setblocking(0)
                self.connections.append(Connection(client, addr))
                print("Got new connection!")
            except BlockingIOError:
                pass
            sleep(self.threadDelay)

    def end(self):
        for conn in self.connections:
            conn.client.close()
        self.socket.shutdown(socket.SHUT_RDWR)
        self.socket.close()
        print("Closing thread")
        self.running = False
        self.thread.join()

