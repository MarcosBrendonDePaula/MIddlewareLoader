import binascii
import struct

class Buffer:

    DefaultSize = 1450

    def __init__(self, str_ = ""):
        if isinstance(str_,str):
            self.Data = str_.encode()
        else:
            self.Data = str_
        self.ActualSize   = len(str_)

    def __str__(self):
        return self.Data.decode("utf-8")

    def setData(self,str_=[]):
        if isinstance(str_,str):
            self.Data = str_.encode()
        else:
            self.Data = str_
        self.ActualSize = len(str_)
        self.Data       = str_
        pass

    def getBytes(self):
        return self.Data

    def __index__(self, index):
        return self.Data[index]