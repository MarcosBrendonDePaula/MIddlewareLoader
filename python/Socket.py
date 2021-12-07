import socket
from Buffer import Buffer
class Socket:
    def __init__(self):
        self.socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.port  = 25565
        self.ip    = ""
    def Bind(self):
        self.socket.bind(self.ip,self.port)
    def Listen(self):
        self.socket.listen(10)
    def Connect(self,Ip = "127.0.0.1",Port = 25565):
        self.socket.connect((Ip,Port))

    def SendBuffer(self,buffer = Buffer()):
        self.socket.send(buffer.getBytes(),0)

    def RecvBuffer(self,BufferSize = Buffer.DefaultSize):
        temp = Buffer()
        temp.setData(self.socket.recv(BufferSize,0))
        return temp