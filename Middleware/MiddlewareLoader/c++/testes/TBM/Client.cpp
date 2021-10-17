#include <iostream>
#include "../../MiddlewareLoader/Tcp/SyncClient.h"

int main() {
    std::string ip;
    std::cin>> ip;
    int buffer = 1500;
    std::cin>>buffer;
    for(int size = 200;size<=1400;size+=200) {
        std::string x = "";
        for(auto a=0;a<size;a++) {
            x+=" ";
        }
        for(int i=0;i<2;i++) {
            SyncClient cli;
            cli.connect_(ip,25565,size);
            std::cout<<"Conectado: "<<cli.isConnected()<<" teste:"<<i<<" size:"<<size<<std::endl;

            for(int i=0;i<5000;i++) {
                cli.sendBuffer(Buffer(x));
                cli.recvBuffer();
            }
            
            cli.disconnect();
        }
    }
	
	std::string x = "";
	for(auto a=0;a<1460;a++) {
		x+=" ";
	}
	
	for(int i=0;i<10;i++) {
		SyncClient cli;
		cli.connect_(ip,25565,1460);
		std::cout<<"Conectado: "<<cli.isConnected()<<" teste:"<<i<<" size:"<<1460<<std::endl;

		for(int i=0;i<5000;i++) {
			cli.sendBuffer(Buffer(x));
			cli.recvBuffer();
		}
		
		cli.disconnect();
	}
	
	/*
    SyncClient cli;
    cli.connect_(ip,25565,buffer);
    std::cout<<"Conectado: "<<cli.isConnected();
    std::string x = "";
    
    for(auto a=0;a<buffer;a++) {
        x+=" ";
    }

    for(int i=0;;i++) {
        cli.sendBuffer(Buffer(x));
        cli.recvBuffer();
    }
    
    cli.disconnect();
	*/
    
    return 0;
}