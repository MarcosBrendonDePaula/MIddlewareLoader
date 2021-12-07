class ErrorCodes:
    NoError         = 0
    BindError       = 1
    ListenError     = 2
    ConnectionError = 3
    MessageError    = 4

class ErrorMessage:
    def __init__(self):
        self.description = ""
        self.code        = 0