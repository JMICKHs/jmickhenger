cmake_minimum_required(VERSION 3.15)
project(network_cache)

set(CMAKE_CXX_STANDARD 20)

add_executable(network_cache main.cpp info/Info.h info/Codeble.cpp info/Codeble.h info/Info.cpp cache/Cache.cpp cache/Cache.h network/AppNetwork.cpp network/AppNetwork.h network/announcer/Announcer.cpp network/announcer/Announcer.h network/parser/Parser.cpp network/parser/Parser.h network/client/Client.cpp network/client/Client.h tests/main.cpp)