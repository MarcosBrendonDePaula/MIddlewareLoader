#include <iostream>
#include "./Async/ServerTcp.h"
#include "./testClass/SimpleMiddleware.hpp"

int main() {
    ServerTcp sv(25565,-1);

    sv.Use(SimpleMiddleware::Module,EventTypes::Connected,5);

    std::cout<<sv.Start(false).description<<std::endl;

    std::cout<<sv._socket<<std::endl;
    system("pause");
    std::cout << "Hello, World! " << std::endl;
    return 0;
}
