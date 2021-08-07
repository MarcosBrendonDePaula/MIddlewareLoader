#include <iostream>
#include "./Async/ServerTcp.h"
#include "./Async/ClientTcp.h"
#include "./testClass/SimpleMiddleware.hpp"

int main() {
    /*
    /**
     * Servidor Middleware
     */
    ServerTcp sv(25565,-1);

    ClientTcp cli;
    cli.Use(SimpleMiddleware::RESPONSECliente,EventTypes::Received,5);
    cli.connect_("127.0.0.1",25565,1500,false);
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
