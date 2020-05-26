cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(app main.cpp)


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


include_directories(BEFORE /usr/local/Cellar/openssl@1.1/1.1.1g/include)
find_library(OPENSSL_LIB ssl PATHS /usr/local/Cellar/openssl@1.1/1.1.1g/lib NO_DEFAULT_PATH)
find_library(CRYPTO_LIB crypto PATHS /usr/local/Cellar/openssl@1.1/1.1.1g/lib NO_DEFAULT_PATH)


find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(app main.cpp)

add_subdirectory(netlib)
target_link_libraries(app netlib)

target_link_libraries(netlib ${Boost_LIBRARIES} ${OPENSSL_LIB} ${CRYPTO_LIB})

