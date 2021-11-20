#include <iostream>
#include <fstream>
#include <map>

#include "../../../MiddlewareLoader/Tcp/AsyncServer.h"
#include "./ModuloHttp/modulo.hpp"
#include "./ModuloHttp/websocket/modulo.hpp"

int main() {
    WebSocket::Debug = true;
    AsyncServer server(25565);
    server.Use(new WebSocket(),EventTypes::Received,1);
    server.Use(new HttpServer(),EventTypes::Received);
    server.Use(new RemoveInstances(),EventTypes::Disconnected);
    server.Start(false);

    return 0;
}