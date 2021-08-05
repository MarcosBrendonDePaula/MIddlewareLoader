//
// Created by Marcos on 04/08/2021.
//

#include "Socket.h"
WSAData Socket::windowsDl;
bool Socket::windowsSockDlInit = false;

/**
 * Caso o sistema operaçional seja windows a biblioteca referente ao gerenciamento do _socket será carregada
 */
Socket::Socket() {
    if(!Socket::windowsSockDlInit) {
        if(WSAStartup(MAKEWORD(2,2),&Socket::windowsDl) == 0) {
            Socket::windowsSockDlInit = true;
        }
    }
    std::memset(&this->sockData,0x0,sizeof(this->sockData));
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
}