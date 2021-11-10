#!/usr/bin/env python
from communication import Commnunication
from time import sleep

c = Commnunication()
c.startServer()
try:
    while True:
        for conn in c.connections:
            data = conn.receive(32)
            if (data != ""):
                print("from: {}, Data: {}".format(conn.addr, data))

                # Echo back
                conn.send("{}@".format(data))
        sleep(1)
except KeyboardInterrupt:
    print("Ending")
    c.end()
except BaseException as e:
    c.end
    raise e
