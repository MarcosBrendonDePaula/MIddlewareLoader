//
// Created by Marcos on 05/08/2021.
//
#pragma once
#include "../MiddlewareModule.h"
#include "../Async/ServerTcp.h"
#include "../Async/ClientTcp.h"
#include <map>
#include <iostream>

namespace SimpleMiddleware {
    using namespace std;
    void Main(std::map<std::string, void *> & Args){
        /*
        Default Args;
        ArgName-----------------CastingType---------
        Args["Server"]          type: ServerTcp*
        Args["Client"]          type: ServerClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
        --------------------------------------------
        */
        cout<<"alguem conectou!"<<endl;
    }

    void Main1(std::map<std::string, void *> & Args){
        /*
        Default Args;
        ArgName-----------------CastingType---------
        Args["Server"]          type: ServerTcp*
        Args["Client"]          type: ServerClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
        --------------------------------------------
        */
        cout<<"Response"<<endl;
        Buffer *res = (Buffer*)Args["Buffer"];

    }

    void MainCliente(std::map<std::string, void *> & Args){
        /*
        Default Args;
        ArgName-----------------CastingType---------
        Args["Server"]          type: ServerTcp*
        Args["Client"]          type: ServerClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
        --------------------------------------------
        */
        cout<<"Response"<<endl;
        Buffer *res = (Buffer*)Args["Buffer"];
        ClientTcp *cli = (ClientTcp*)Args["Client"];
        cout<<"Buffer: "<<res->toString()<<endl;
        cli->sendBuffer(Buffer("OK"));
    }

    //Função necessaria para remover instancias criadas e passadas a outros middlewares
    //caso não exista as instancias ficaram ocupando memoria
    void RemoveCustomArgs(std::map<std::string, void *> & Args) {
        /*
        Default Args;
        ArgName-----------------CastingType---------
        Args["Server"]          type: ServerTcp*
        Args["Client"]          type: ServerClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
        --------------------------------------------
        */
        cout<<"Removendo CustomArgs"<<endl;
    }

    MiddlewareModule CONNECT(Main,NULL);
    MiddlewareModule RESPONSE(Main1,NULL);
    MiddlewareModule RESPONSECliente(NULL,MainCliente);
    MiddlewareModule REMOVEARGS(RemoveCustomArgs,NULL);
}