import binascii
import struct

class Buffer:
    def __init__(self, str_, maxBuffer = 1500):
        self.Data         = ""
        self.ActualBuffer = 0
        self.MaxBuffer    = 0

        if str_:
            self.Data = struct.Struct('I 2s f')
            #self.ActualBuffer = len(self.Data)

    def __str__(self):
        return str.encode(self.str_)