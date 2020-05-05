cmake_minimum_required(VERSION 3.15)
project(netlib)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(netlib main.cpp announcer/Announcer.cpp announcer/Announcer.h info/Info.cpp info/Info.h parser/Parser.cpp parser/Parser.h client/Client.cpp client/Client.h AppNetwork.cpp AppNetwork.h cache/Cache.cpp cache/Cache.h)
target_link_libraries(netlib ${Boost_LIBRARIES})