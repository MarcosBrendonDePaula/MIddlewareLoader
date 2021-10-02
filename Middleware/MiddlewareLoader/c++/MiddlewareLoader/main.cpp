#include <iostream>
#include "./Tcp/AsyncServer.h"
#include "./Tcp/AsyncClient.h"
#include "./Tcp/SyncClient.h"

#include "./Middleware/Middleware.h"
#include "./Middleware/Node.h"
int main() {
    /*
    /**
     * Servidor Middleware
     * Loop infinito
     */
    Middleware*      MD = Middleware::Make();
    NodeManipulator* NM = NodeManipulator::Make();

    AsyncServer server(25565,-1);
    server.Use(MD->Modulo,EventTypes::Connected,5);
    server.Start(false);

    return 0;
}
