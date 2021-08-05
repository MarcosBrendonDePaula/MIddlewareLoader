//
// Created by Marcos on 04/08/2021.
//

#include "ServerTcp.h"
void ServerTcp::loopFunction(ServerTcp *Server) {
    while (Server->listening) {
        int clientDataLen = sizeof(Server->clients[Server->idCounter].sockData);

        Server->clients[Server->idCounter]._socket = accept(Server->_socket,(struct sockaddr*)&Server->sockData,&clientDataLen);
        Server->clients[Server->idCounter].setId(Server->idCounter);
        Server->clients[Server->idCounter].setFather(Server);
        Server->clients[Server->idCounter].Start();


        std::map<std::string,void*> Args;

        for(auto event : Server->events[(int)EventTypes::Connected]) {
            if(event.ServerMain!=NULL)
                event.ServerMain(Args);
        }
        Server->idCounter+=1;
    }
}

ServerTcp::ServerTcp(int port, int limit) : port(port), limit(limit) {
    this->events = std::vector<std::vector<MiddlewareModule>>(10);
}

ErrorMessage ServerTcp::Use(MiddlewareModule module, EventTypes event, int priority) {
    ErrorMessage DEFAULT;
    DEFAULT.code = ErrorCodes::NoError;

    module.priority = priority;

    this->events[(int)event].push_back(module);

    std::sort(this->events[(int)event].begin(),this->events[(int)event].end());
    return DEFAULT;
}

ErrorMessage ServerTcp::Start(bool detach) {
    this->idCounter = 0;
    ErrorMessage DEFAULT;
    DEFAULT.code = ErrorCodes::NoError;
    DEFAULT.description="OK";

    this->sockData.sin_family = AF_INET;
    this->sockData.sin_port = htons(this->port);
    this->sockData.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(this->_socket, (struct sockaddr *) &this->sockData, sizeof(this->sockData)) < 0){
        closesocket(this->_socket);
        DEFAULT.code = ErrorCodes::BindError;
        DEFAULT.description = "Bind Error";
        return DEFAULT;
    }

    if (listen(this->_socket, this->limit) < 0){
        closesocket(this->_socket);
        DEFAULT.code = ErrorCodes::ListenError;
        DEFAULT.description = "Listen Error";
        return DEFAULT;
    }

    this->listening = true;
    this->loopThread = std::thread(this->loopFunction,this);
    if(detach)
        this->loopThread.detach();
    else
        this->loopThread.join();
    return DEFAULT;
}


//----------------------------------------------------------------------------Client Server

bool ServerClient::isConnected() const {
    return connected;
}

void ServerClient::setConnected(bool connected) {
    ServerClient::connected = connected;
}

int & ServerClient::getId() {
    return id;
}

void ServerClient::setId(int id) {
    ServerClient::id = id;
}

void ServerClient::Start() {
    this->loopThread = std::thread(this->loopFunction,this);
    this->connected = true;
    this->loopThread.detach();
}

ServerTcp *ServerClient::getFather() const {
    return father;
}

void ServerClient::setFather(ServerTcp *father) {
    ServerClient::father = father;
}

void ServerClient::loopFunction(ServerClient *Client) {
    while(Client->connected){
        auto buffer = Buffer(Client->father->DEFAULTBUFFERSIZE);
        buffer.setActualSize(-1);
        buffer.setActualSize(recv(Client->_socket,buffer[0],Client->father->DEFAULTBUFFERSIZE,0));
        if(buffer.getActualSize()<=0) {
            return;
        }
        std::cout<<buffer.toString()<<std::endl;

    }
}

ServerClient::ServerClient() {}
