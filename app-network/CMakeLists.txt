cmake_minimum_required(VERSION 3.9)
project(app_network)

set(CMAKE_CXX_STANDARD 17)

add_executable(app_network main.cpp AppNetwork.cpp AppNetwork.h info/Codeble.cpp info/Codeble.h client/Client.cpp client/Client.h announser/Announcer.cpp announser/Announcer.h parser-json/Parser.cpp parser-json/Parser.h info/Info.h)