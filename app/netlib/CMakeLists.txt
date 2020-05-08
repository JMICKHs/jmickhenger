cmake_minimum_required(VERSION 3.15)
project(netlib)

set(CMAKE_CXX_STANDARD 20)
set(SOURCES  announcer/Announcer.cpp
    announcer/Announcer.h
    info/Info.cpp
    info/Info.h
    parser/Parser.cpp
    parser/Parser.h
    client/Client.cpp
    client/Client.h
    AppNetwork.cpp
    AppNetwork.h
    cache/Cache.cpp
    cache/Cache.h)

add_library(netlib SHARED ${SOURCES})

