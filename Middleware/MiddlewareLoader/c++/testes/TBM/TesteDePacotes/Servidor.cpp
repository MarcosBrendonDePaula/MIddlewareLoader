#include <iostream>
#include <string>
#include "../../MiddlewareLoader/Tcp/AsyncServer.h"
#include "../../MiddlewareLoader/MiddlewareModule.h"
#include <vector>
#include <chrono>
#include <type_traits>
#include <fstream>

int teste = 0;
int size = 100;
double media = 0;
int qt=0;

auto start = std::chrono::high_resolution_clock::now();

std::chrono::system_clock::rep time_since_epoch(){
    static_assert(
        std::is_integral<std::chrono::system_clock::rep>::value,
        "Representation of ticks isn't an integral value."
    );
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

std::vector<std::pair<std::chrono::duration<double, std::milli>,int>> times;
class RelayMsg:public MiddlewareModule{
    void Main(std::map<std::string,void*>& Args) {
        auto finish = std::chrono::high_resolution_clock::now();
        auto client = (ServerClient*) Args["Client"];
        auto bf     = (Buffer*)Args["Buffer"];
        std::chrono::duration<double, std::milli> elapsed = finish-start;
        times.push_back(std::make_pair(elapsed,bf->getActualSize()));
        start = std::chrono::high_resolution_clock::now();
        client->sendBuffer(*bf);
    }
};

class finalize:public MiddlewareModule{
    void Main(std::map<std::string,void*>& Args) {
        auto Server = (AsyncServer*)Args["Server"];
        std::ofstream myfile;
        auto tname = std::to_string(teste);
        myfile.open(tname+".csv",std::ios::out);
        for(auto i : times){
            myfile<<i.first.count()<<","<<i.second<<";\n";
        }
        myfile.close();
        teste+=1;
        times = std::vector<std::pair<std::chrono::duration<double, std::milli>,int>>();
    }
};




int main() {
    /*
    /**
     * Servidor Middleware
     * Loop infinito
     */
    
    AsyncServer server(25565,-1);
    server.DEFAULTBUFFERSIZE = 10000;
    server.Use(new RelayMsg(),EventTypes::Received,5);
    server.Use(new finalize(),EventTypes::Disconnected,5);
    server.Start(false);
    
    return 0;
}
