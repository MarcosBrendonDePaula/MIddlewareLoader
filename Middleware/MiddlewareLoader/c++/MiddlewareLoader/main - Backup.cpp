#include <iostream>
#include "./Tcp/AsyncServer.h"
#include "./Tcp/AsyncClient.h"
#include "./Tcp/SyncClient.h"

/*
 * SERVER:
    Default Args;
    ArgName-----------------CastingType---------
    Args["Server"]          type: AsyncServer*
    Args["Client"]          type: ServerClient*
    Args["Buffer"]          type: Buffer*
    Args["ErrorMessage"]    type: ErrorMessage*
--------------------------------------------
*/

/*
 * CLIENT:
    Default Args;
    ArgName-----------------CastingType---------
    Args["Client"]          type: AsyncClient*
    Args["Buffer"]          type: Buffer*
    Args["ErrorMessage"]    type: ErrorMessage*
--------------------------------------------
*/


void ResponseServer(std::map<std::string,void*>& Args) {
    ServerClient* Client =(ServerClient*) Args["Client"];
    std::cout<<"Servidor recebeu!"<<std::endl;
    Client->sendBuffer(Buffer("Conectado"));
}

void Connect(std::map<std::string,void*>& Args) {
    ServerClient* Client =(ServerClient*) Args["Client"];
    std::cout<<"server:"<<Buffer("Conectado").toString()<<std::endl;
    Client->sendBuffer(Buffer("Conectado"));
}

void ResponseClient(std::map<std::string,void*>& Args) {
    AsyncClient* Client =(AsyncClient*) Args["Client"];
    std::cout<<"Client recebeu!"<<std::endl;
    Client->sendBuffer(Buffer("OK!"));

}

MiddlewareModule ConnectModule(Connect,NULL);
MiddlewareModule ResponseModule(ResponseServer,ResponseClient);

int main() {
    /*
    /**
     * Servidor Middleware
     * Loop infinito
     */
    AsyncServer sv(25565,-1);
    sv.Use(ConnectModule,EventTypes::Connected,5);
    sv.Use(ResponseModule,EventTypes::Received);
    sv.Start(true);

    AsyncClient cli;
    cli.Use(ConnectModule,EventTypes::Connected,5);
    cli.Use(ResponseModule,EventTypes::Received);
    cli.connect_("127.0.0.1",25565,1500,true);

    SyncClient teste;

    auto res = teste.connect_("127.0.0.1",25565);

    if(teste.isConnected()) {
        std::cout<<"Conectado! code:"<<res.code<<" desc:"<<res.description<<std::endl;
        while(teste.isConnected()) {
            teste.sendBuffer(Buffer("Ok"));
            std::cout<<"Sync client res: "<<teste.recvBuffer().toString()<<std::endl;
        }
    }
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
