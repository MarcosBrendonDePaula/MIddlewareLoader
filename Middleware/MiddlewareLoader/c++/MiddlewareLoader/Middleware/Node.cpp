//
// Created by Marcos on 24/09/2021.
//

#include "Node.h"
NodeManipulator* NodeManipulator::Obj = nullptr;

NodeManipulator * NodeManipulator::Make() {
    if(NodeManipulator::Obj == nullptr) {
        NodeManipulator::Obj = new NodeManipulator();
    }
    return NodeManipulator::Obj;
}

NodeManipulator::NodeManipulator() {

}

void NodeManipulator::NodeRegister(std::string Lang,std::string Name,ServerClient* Client) {
    auto novoNode = Node();

    novoNode.Lang   = Lang;
    novoNode.Name   = Name;
    novoNode.Client = Client;

    this->Nodes[Name] = novoNode;
}