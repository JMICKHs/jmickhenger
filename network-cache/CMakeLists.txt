cmake_minimum_required(VERSION 3.15)
project(network_cache)

set(CMAKE_CXX_STANDARD 20)

add_executable(network_cache main.cpp network/info/Info.h network/info/Codeble.cpp network/info/Codeble.h network/info/Info.cpp network/cache/Cache.cpp network/cache/Cache.h network/AppNetwork.cpp network/AppNetwork.h network/announcer/Announcer.cpp network/announcer/Announcer.h network/parser/Parser.cpp network/parser/Parser.h network/client/Client.cpp network/client/Client.h tests/main.cpp)