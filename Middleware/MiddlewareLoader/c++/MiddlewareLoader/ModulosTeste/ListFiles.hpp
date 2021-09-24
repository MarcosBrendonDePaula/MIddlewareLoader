#include "../MiddlewareModule.h"
#include "../Tcp/AsyncServer.h"
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;
 
class ListFiles:MiddlewareModule{
    public:
        static ListFiles* __Obj;
        static ListFiles* __Make(std::string);
        std::string dir;
        ListFiles(std::string);
};

ListFiles* ListFiles::__Obj = nullptr;

ListFiles* ListFiles::__Make(std::string dir) {
    if(ListFiles::__Obj==nullptr) {
        ListFiles::__Obj = new ListFiles(dir);
    }
    return ListFiles::__Obj;
}


ListFiles::ListFiles(std::string dir) {
    this->dir = dir;
    ServerMain = [](std::map<std::string,void*>& Args){
        auto LF = ListFiles::__Make("");
        auto files = new std::vector<std::string>();
        for (const auto & entry : fs::directory_iterator(LF->dir)){
            files->push_back(entry.path().string());
        }
        Args["files"] = files;
    };
}