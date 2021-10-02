//
// Created by Marcos on 24/09/2021.
//

#ifndef MIDDLEWARELOADER_MIDDLEWARE_H
#define MIDDLEWARELOADER_MIDDLEWARE_H

#include "../MiddlewareModule.h"
#include "../Tcp/SyncClient.h"
#include "./Config.h"
class Middleware{
public:
    static Middleware* Obj;
    static Middleware* Make();

    template<class type> static void SendVariable(type obj,std::string alvo);
    template<class type> static void SendVector(type obj[],std::string alvo);

    template<class type> static void RecvVariable(std::string alvo);
    template<class type> static void RecvVector(std::string alvo);

    std::map<std::string,SyncClient> Connections;
    MiddlewareModule Modulo;
    MiddlewareModule RecvModulo;

    Middleware();
    static void ReciveMesage(std::map<std::string,void*>& Args);
    static void ConnectMain_(std::map<std::string,void*>& Args);
private:
};


#endif //MIDDLEWARELOADER_MIDDLEWARE_H
