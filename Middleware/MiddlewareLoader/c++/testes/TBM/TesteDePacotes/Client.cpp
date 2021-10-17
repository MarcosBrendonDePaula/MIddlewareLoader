#include <iostream>
#include "../../MiddlewareLoader/Tcp/SyncClient.h"

int main() {
    std::string ip;
    std::cin>> ip;
    int buffer = 1500;
    std::cin>>buffer;
    for(int size = 710;size<=1410;size+=100) {
        std::string x = "";
        for(auto a=0;a<size;a++) {
            x+=" ";
        }
        for(int i=0;i<10;i++) {
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
    
	for(int i=0;i<10;i++) {
		SyncClient cli;
		cli.connect_(ip,25565,1460);
		std::cout<<"Conectado: "<<cli.isConnected()<<" teste:"<<i<<" size:"<<size<<std::endl;

		for(int i=0;i<5000;i++) {
			cli.sendBuffer(Buffer(x));
			cli.recvBuffer();
		}
		
		cli.disconnect();
	}
	
    return 0;
}