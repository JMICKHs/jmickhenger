cmake_minimum_required(VERSION 3.15)
project(network_cache)

set(CMAKE_CXX_STANDARD 20)


configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)

add_executable(network_cache main.cpp network/info/Info.h network/info/Codeble.h network/info/Info.cpp network/cache/Cache.cpp network/cache/Cache.h network/AppNetwork.cpp network/AppNetwork.h network/announcer/Announcer.cpp network/announcer/Announcer.h network/parser/Parser.cpp network/parser/Parser.h network/client/Client.cpp network/client/Client.h)