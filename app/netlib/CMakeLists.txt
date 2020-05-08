cmake_minimum_required(VERSION 3.15)
project(netlib)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*/*.h")

add_library(netlib SHARED ${SOURCES})

