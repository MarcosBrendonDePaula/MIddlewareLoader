#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include "../../../../../MiddlewareLoader/Tcp/AsyncServer.h"
#include "../bodyparser.hpp"
#include "../http/json.hpp"
#include "../http/Utility.hpp"
#include "../http/sha1/sha1.hpp"
#include "../http/base64/base64.hpp"

using namespace std;

class WebsocketInstance{
    public:
        WebsocketInstance();
        Socket* client;
        bool connected;
};

WebsocketInstance::WebsocketInstance() {
    this->connected = false;
}

class WebSocket : public MiddlewareModule{
    private:
        std::map<Socket*, WebsocketInstance> sockets;
    public:
        static bool Debug;
        void Main(map<string,void *>&Args) {
            auto client = (ServerClient*)Args["Client"];
            
            if(this->sockets[client].connected) {
                if(WebSocket::Debug) {
                    std::cout<<"WebSocket is connected"<<std::endl;
                }
                while(true) {
                    auto recved = this->sockets[client].client->recvBuffer();
                    std::cout<<recved.getActualSize()<<" Received:"<<(char*)&recved.getData()[0]<<std::endl;
                    std::cout<<recved.getActualSize()<<" Received:"<<websocketpp::base64_decode(recved.toString())<<std::endl;
                }
            }
            
            if(WebSocket::Debug) {
                std::cout<<"WebSocket HandShake"<<std::endl;
            }

            easy::Header::Request req(((Buffer*)Args["Buffer"])->toString());
            if(req.Header["Upgrade"]=="websocket"){
                
                bool *answered = new bool;
                *answered = true;
                Args["answered"] = answered;

                std::string Key = req.Header["Sec-WebSocket-Key"];

                auto newKey = Key+ "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
                std::cout<<"New key:"<<newKey<<std::endl;

                char hex[SHA1_HEX_SIZE];
                char base64[SHA1_BASE64_SIZE];
                auto sh = sha1(newKey.c_str());
                sh.finalize();
                sh.print_base64(base64);

                std::string header = 
                std::string("HTTP/1.1 101 Switching Protocols\r\n")+
                std::string("Upgrade: websocket\r\n")+
                std::string("Connection: Upgrade\r\n")+
                std::string("Sec-WebSocket-Accept: "+std::string(base64)+"\r\n\r\n");

                client->sendBuffer(Buffer(header));

                this->sockets[client].connected = true;
                this->sockets[client].client = client;

                if(WebSocket::Debug) {
                    std::cout<<"WebSocket Base64 key:"<<base64<<" Accepted"<<std::endl;
                }

            }else{
            }
            
        }
        WebSocket() {
        }
};
bool WebSocket::Debug = false;