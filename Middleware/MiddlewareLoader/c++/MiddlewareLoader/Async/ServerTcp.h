//
// Created by Marcos on 04/08/2021.
//

#ifndef MIDDLEWARELOADER_SERVERTCP_H
#define MIDDLEWARELOADER_SERVERTCP_H

#include "../Socket.h"
#include "../EventTypes.h"
#include "../ErrorMessage.h"
#include "../Buffer.h"
#include "../MiddlewareModule.h"

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <thread>

class ServerClient;
class ServerTcp : public Socket {
private:
    int port;
    int limit;
    bool listening;
    unsigned int idCounter;
    std::vector<std::vector<MiddlewareModule>> events;
    std::map<unsigned int,ServerClient> clients;

    std::thread loopThread;
    static void loopFunction(ServerTcp* Server);
public:
    int DEFAULTBUFFERSIZE = 1500;
    ServerTcp(int port = 25565, int limit = -1);
    ErrorMessage Use(MiddlewareModule module,EventTypes event,int priority = 5);
    ErrorMessage Start(bool detach = true);
};


class ServerClient : public Socket{
private:
    bool connected;
    int id;
    ServerTcp* father;

    std::thread loopThread;
    static void loopFunction(ServerClient* Client);

public:


    ServerClient();

    void Start();

    ServerTcp *getFather() const;

    void setFather(ServerTcp *father);

    bool isConnected() const;

    void setConnected(bool connected);

    int & getId();

    void setId(int id);
};

#endif //MIDDLEWARELOADER_SERVERTCP_H
