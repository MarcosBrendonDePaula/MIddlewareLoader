#include <iostream>
#include "../MiddlewareLoader/Tcp/AsyncServer.h"
#include "../MiddlewareLoader/Tcp/AsyncClient.h"
#include "../MiddlewareLoader/Tcp/SyncClient.h"

#include "./Middleware.h"
#include "./Node.h"

int main() {
    Middleware*      MD = Middleware::Make();
    NodeManipulator* NM = NodeManipulator::Make();

    AsyncServer server(25565,-1);
    server.Use(MD->Modulo,EventTypes::Connected,5);
    server.Start(false);

    return 0;
}