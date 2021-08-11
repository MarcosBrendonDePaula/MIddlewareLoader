#include <iostream>
#include "./Tcp/AsyncServer.h"
#include "./Tcp/SyncClient.h"

void Connect(std::map<std::string,void*>& Args) {
    ServerClient* Client =(ServerClient*) Args["Client"];
    std::cout<<"server:"<<Buffer("Conectado").toString()<<std::endl;
    Client->sendBuffer(Buffer("Conectado"));
}
MiddlewareModule ConnectModule(Connect,NULL);

int main() {
    /*
    /**
     * Servidor Middleware
     */
    AsyncServer sv(25565,-1);
    sv.Use(ConnectModule,EventTypes::Connected,5);
    sv.Start(false);

    /**
     * Registro de Eventos.
     * Modulo,EventType,prioridade,
     *                  quanto menor o valor maior a prioridade
        *//*
    sv.Use(SimpleMiddleware::CONNECT,EventTypes::Connected,5);
    sv.Use(SimpleMiddleware::RESPONSE,EventTypes::Received,5);
    sv.Use(SimpleMiddleware::REMOVEARGS,EventTypes::Received,6);

    sv.Start(false);
    */

    return 0;
}
