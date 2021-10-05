#!/bin/python

class request:
    def __init__(self, estampille, start, type, address, size):
        self.estampille = estampille
        self.stat = start
        self.type = type
        self.address = address
        self.size = size

if __name__ == "__main__":
    r = request(10, 0, 1, 0, 50)
    print("here {}".format(request.estampille))
