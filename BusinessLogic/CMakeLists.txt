cmake_minimum_required(VERSION 3.15)
project(Messenger_Logic)

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
add_subdirectory(test)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)

find_package (Boost REQUIRED)
find_package(Threads REQUIRED)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(${LIBMONGOCXX_INCLUDE_DIRS})
link_directories(${LIBBSONCXX_INCLUDE_DIR})
link_directories(${Boost_INCLUDE_DIRS})

file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*/*.cpp"
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*/*.h"
        "${PROJECT_SOURCE_DIR}/*.hpp"
        "${PROJECT_SOURCE_DIR}/*/*.hpp")

add_library(Messenger_Logic SHARED ${SOURCES})

target_link_libraries(Messenger_Logic ${LIBMONGOCXX_LIBRARIES} ${lIBBSONCXX_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

