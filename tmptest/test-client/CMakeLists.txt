cmake_minimum_required(VERSION 3.15)
project(test_client)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(test_client main.cpp parser/Parser.h info/Info.h parser/Parser.cpp info/Info.cpp)
target_link_libraries(test_client ${Boost_LIBRARIES})