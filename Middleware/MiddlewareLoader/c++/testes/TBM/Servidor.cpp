#include <iostream>
#include <string>
#include "../../MiddlewareLoader/Tcp/AsyncServer.h"
#include "../../MiddlewareLoader/MiddlewareModule.h"
#include <vector>
#include <chrono>
#include <type_traits>
#include <fstream>
#include <sstream>

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

std::vector<std::chrono::system_clock::rep> times;
class RelayMsg:public MiddlewareModule{
    void Main(std::map<std::string,void*>& Args) {
        auto client = (ServerClient*) Args["Client"];
        auto bf     = (Buffer*)Args["Buffer"];
        client->sendBuffer(*bf);
        times.push_back(time_since_epoch());
    }
};

class finalize:public MiddlewareModule{
    void Main(std::map<std::string,void*>& Args) {
        auto Server = (AsyncServer*)Args["Server"];
        std::ofstream myfile;
        auto tname = std::to_string(teste);
        myfile.open(tname+".csv",std::ios::out);
        for(auto i : times){
            std::string number;
            std::stringstream strstream;
            strstream << i;
            strstream >> number;
            myfile<<number<<";\n";
        }
        myfile.close();
        teste+=1;
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
