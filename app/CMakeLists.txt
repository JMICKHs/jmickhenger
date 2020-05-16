cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(app main.cpp)

add_subdirectory(netlib)
target_link_libraries(app netlib)

target_link_libraries(netlib ${Boost_LIBRARIES})


#gtests
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

#unitTesting
enable_testing()
add_subdirectory(tests-netlib)
