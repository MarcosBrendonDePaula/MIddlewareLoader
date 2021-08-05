//
// Created by Marcos on 05/08/2021.
//
#pragma once
#include "../MiddlewareModule.h"
#include <map>
#include <iostream>

namespace SimpleMiddleware {
    using namespace std;
    void Main(std::map<std::string, void *> & Args){
        cout<<"alguem conectou!"<<endl;
    }

    void Main1(std::map<std::string, void *> & Args){
        cout<<"priority!"<<endl;
    }

    MiddlewareModule Module(Main,NULL);
    MiddlewareModule Module1(Main1,NULL);
}