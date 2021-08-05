cmake_minimum_required(VERSION 3.19)
project(MiddlewareLoader)

set(CMAKE_CXX_STANDARD 20)

link_libraries(ws2_32)
add_executable(MiddlewareLoader main.cpp Socket.cpp Socket.h MiddlewareModule.cpp MiddlewareModule.h ErrorMessage.cpp ErrorMessage.h EventTypes.cpp EventTypes.h Buffer.cpp Buffer.h Async/ServerTcp.cpp Async/ServerTcp.h testClass/SimpleMiddleware.hpp)