//
// Created by Marcos on 04/08/2021.
//

#ifndef MIDDLEWARELOADER_SOCKET_H
#define MIDDLEWARELOADER_SOCKET_H

#include <winsock2.h>
#include <cstring>

class Socket {
public:
    Socket();
    int _socket;
    sockaddr_in sockData;
    /**
     * Windows dll loader
     */
    static WSAData windowsDl;
    static bool windowsSockDlInit;
protected:

};


#endif //MIDDLEWARELOADER_SOCKET_H
