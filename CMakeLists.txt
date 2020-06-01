#cmake_minimum_required(VERSION 2.6)
##PROJECT(boost-asio-examples)
#PROJECT(tcp)
###
#### Test definitions ###
###
##
##configure_file(CMakeLists.txt.in
##        googletest-download/CMakeLists.txt)
##execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
##        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
##execute_process(COMMAND ${CMAKE_COMMAND} --build .
##        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
##
##add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
##        ${CMAKE_BINARY_DIR}/googletest-build)
##
##enable_testing()
##add_subdirectory(Tests)
####
##### Test definitions end ###
####
#
#SET(Boost_USE_STATIC_LIBS OFF)
#SET(Boost_USE_MULTITHREAD ON)
#FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
#IF(Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#ENDIF(Boost_FOUND)
#
#SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
#
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=checkedCntr++17 -pthread")
##set(CMAKE_CXX_STANDARD 20)
#
#
#
##ADD_EXECUTABLE(async_server RunServer.cpp Source/Server/Server.cpp Source/Connection/Connection.cpp)
##ADD_EXECUTABLE(async_server Source/jopa/server.cpp)
##ADD_EXECUTABLE(async_client Source/jopa/client.cpp)
#ADD_EXECUTABLE(async_server RunServer.cpp Source/Server/Server.cpp Source/Connection/Connection.cpp Source/BusinessLogicProxy/BusinessLogicProxy.cpp Source/Server/WorkerThread.cpp)
#TARGET_LINK_LIBRARIES(async_server ${USED_LIBS})
#
#
#ADD_EXECUTABLE(async_client Source/async_client_for_serGay/async_client_always_listen.cpp Source/jopa/client.cpp Source/jopa/server.cpp)
#TARGET_LINK_LIBRARIES(async_client ${USED_LIBS})

cmake_minimum_required(VERSION 3.10.2)
project(test_client)

set(CMAKE_CXX_STANDARD 17)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.65.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)
find_package(OpenSSL REQUIRED)

link_directories(${Boost_INCLUDE_DIRS})

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)


include_directories(${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(${LIBMONGOCXX_INCLUDE_DIRS})
link_directories(${LIBBSONCXX_INCLUDE_DIR})



SET(USED_LIBS ${Boost_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")

add_executable(async_client Source/async_client_for_serGay/async_client_always_listen.cpp)
ADD_EXECUTABLE(server RunServer.cpp
        Source/Server/Server.cpp
        Source/Connection/Connection.cpp
        Source/BusinessLogicProxy/BusinessLogicProxy.cpp
        Source/Server/WorkerThread.cpp
        )

add_subdirectory(Source/BusinessLogic)
target_link_libraries(server ${USED_LIBS} BusinessLogic OpenSSL::SSL)
target_link_libraries(async_client ${USED_LIBS})
