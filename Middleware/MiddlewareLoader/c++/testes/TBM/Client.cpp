#include <iostream>
#include "../../MiddlewareLoader/Tcp/SyncClient.h"

int main() {
    std::string ip;
    std::cin>> ip;
    
    std::string x = "";
    for(auto a=0;a<1500;a++) {
        x+="a";
    }

    for(int i=0;i<40;i++) {
        SyncClient cli;
        cli.connect_(ip,25565,1500);
        std::cout<<"Conectado: "<<cli.isConnected();

        for(int i=0;i<5000;i++) {
            cli.sendBuffer(Buffer(x));
            cli.recvBuffer();
        }
        
        cli.disconnect();
    }
    return 0;
}