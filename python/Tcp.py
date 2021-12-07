from Socket import Socket
from MiddlewareModule import MiddlewareModule
import threading

class AsyncServer(Socket):

    def __init__(self,Port = 25565):
        self.Clients = {}
        self.Events  = [[],[],[],[],[],[]]
        self.Thread_Loop = None
        super().port = Port

    def Use(self,Module = MiddlewareModule(),OnEvent = 0,Priority=None):
        if Priority:
            Module.priority = Priority
        self.Events[OnEvent].append(Module)

    def Start(self,datach = True):
        super().Bind();
        super().Listen();
        if datach:
            self.Thread_Loop = threading.Thread(target = AsyncServer.__Accept_Loop__ , args=(self,))
            self.Thread_Loop.start()
        else:
            AsyncServer.__Accept_Loop__(self)

    @staticmethod
    def __Accept_Loop__(obj):

        pass
    pass