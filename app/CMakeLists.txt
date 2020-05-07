cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(app main.cpp)

add_subdirectory(netlib)
target_link_libraries(app netlib)

target_link_libraries(netlib ${Boost_LIBRARIES})