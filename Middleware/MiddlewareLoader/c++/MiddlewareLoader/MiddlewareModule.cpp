//
// Created by Marcos on 04/08/2021.
//

#include "MiddlewareModule.h"

bool MiddlewareModule::operator<(MiddlewareModule check) {
    return this->priority<check.priority;
}

MiddlewareModule::MiddlewareModule(void (*ServerMain)(std::map<std::string, void *> &), void (*ClientMain)(std::map<std::string, void *> &)) {
    this->ServerMain = ServerMain;
    this->ClientMain = ClientMain;
}
