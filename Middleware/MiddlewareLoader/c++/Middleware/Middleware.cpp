//
// Created by Marcos on 24/09/2021.
//

#include "Middleware.h"
#include "../MiddlewareLoader/Tcp/AsyncServer.h"
#include "Node.h"

Middleware* Middleware::Obj = nullptr;

Middleware * Middleware::Make() {
    if(Middleware::Obj == nullptr)
        Middleware::Obj = new Middleware();
    return  Middleware::Obj;
}

template<class type> void Middleware::SendVariable(type obj, std::string alvo) {
    while(!NodeManipulator::Nodes[alvo].Connected) {
        if(Config::Debug){
            std::cout<<"Esperando Conexão"<<endl;
        }
        Sleep(100)
    }
    
}

template<class type> void Middleware::SendVector(type *obj, std::string alvo) {
    while(!NodeManipulator::Nodes[alvo].Connected) {
        if(Config::Debug){
            std::cout<<"Esperando Conexão"<<endl;
        }
        Sleep(100)
    }
}


Middleware::Middleware() {
    this->Modulo = MiddlewareModule(Middleware::ConnectMain_);
    this->RecvModulo = MiddlewareModule(Middleware::ReciveMesage);
}

void Middleware::ConnectMain_(std::map<std::string, void *> &Args) {
    auto MD = Middleware::Make();
    auto MN = NodeManipulator::Make();

    ServerClient* client = (ServerClient*)Args["Client"];

    //requerindo nome
    auto name     = client->recvBuffer(Config::maxBuffer);
    auto language = client->recvBuffer(Config::maxBuffer);

    MN->NodeRegister(language.toString(),name.toString(),client);

}