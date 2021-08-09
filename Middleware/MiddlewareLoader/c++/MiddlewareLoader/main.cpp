#include <iostream>
#include "./Tcp/AsyncServer.h"
#include "./Tcp/AsyncClient.h"
#include "./testClass/SimpleMiddleware.hpp"

int main() {
    /*
    /**
     * Servidor Middleware
     */
    AsyncServer sv(25565,-1);

    AsyncClient cli;
    cli.Use(SimpleMiddleware::RESPONSE,EventTypes::Received,5);
    std::cout<<cli.connect_("127.0.0.1",25565,1500,false).description<<std::endl;
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
