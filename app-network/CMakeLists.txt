cmake_minimum_required(VERSION 3.15)
project(app_network)

set(CMAKE_CXX_STANDARD 20)

add_executable(app_network main.cpp parser-json/Parser.cpp parser-json/Parser.h info/Info.h info/Codeble.h client/Client.cpp client/Client.h announcer/Announcer.cpp announcer/Announcer.h AppNetwork.cpp AppNetwork.h info/Info.cpp)