cmake_minimum_required(VERSION 3.15)
project(app_network)

set(CMAKE_CXX_STANDARD 20)

add_executable(app_network main.cpp AppNetwork.cpp AppNetwork.h info/Codeble.cpp info/Codeble.h client/Client.cpp client/Client.h announser/Announser.cpp announser/Announser.h parser-json/Parser.cpp parser-json/Parser.h info/Info.h)