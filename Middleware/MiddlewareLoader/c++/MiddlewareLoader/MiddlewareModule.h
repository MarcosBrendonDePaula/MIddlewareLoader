//
// Created by Marcos on 04/08/2021.
//

#ifndef MIDDLEWARELOADER_MIDDLEWAREMODULE_H
#define MIDDLEWARELOADER_MIDDLEWAREMODULE_H
#include <map>
#include <iostream>

class MiddlewareModule {
public:
    /**
     * SERVER:
        Default Args;
        ArgName-----------------CastingType---------
        Args["Server"]          type: AsyncServer*
        Args["Client"]          type: ServerClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
    --------------------------------------------
    */

    /**
     * CLIENT:
        Default Args;
        ArgName-----------------CastingType---------
        Args["Client"]          type: AsyncClient*
        Args["Buffer"]          type: Buffer*
        Args["ErrorMessage"]    type: ErrorMessage*
    --------------------------------------------
    */

    MiddlewareModule(void (*ServerMain)(std::map<std::string, void *> &Args) = NULL, void (*ClientMain)(std::map<std::string, void *> &)= NULL );
    void (*ServerMain)(std::map<std::string,void*>&) = NULL;
    void (*ClientMain)(std::map<std::string,void*>&) = NULL;
    int priority;
    bool operator< (MiddlewareModule check);
private:

};


#endif //MIDDLEWARELOADER_MIDDLEWAREMODULE_H
