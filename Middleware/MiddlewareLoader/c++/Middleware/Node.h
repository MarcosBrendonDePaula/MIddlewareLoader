//
// Created by Marcos on 24/09/2021.
//

#ifndef MIDDLEWARELOADER_NODE_H
#define MIDDLEWARELOADER_NODE_H

#include <iostream>
#include "../MiddlewareLoader/Tcp/AsyncServer.h"
#include "./Config.h"
#include <map>

class Node {
public:
    std::string   Lang;
    std::string   Name;
    bool          Connected;
    ServerClient* Client;
};

class NodeManipulator {
public:
    std::map<std::string,Node> Nodes;
    static NodeManipulator* Obj;
    static NodeManipulator* Make();

    NodeManipulator();
    void NodeRegister(std::string Lang,std::string Name,ServerClient* Client);
};

#endif //MIDDLEWARELOADER_NODE_H
