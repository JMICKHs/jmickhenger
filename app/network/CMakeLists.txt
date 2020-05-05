cmake_minimum_required(VERSION 3.9)
project(network)

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

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})


file(GLOB sources
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/*/*.cpp")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/tests/main.cpp"
                         "${PROJECT_SOURCE_DIR}/tests/tests.cpp")

add_executable(network ${sources} ${Boost_LIBRARIES})