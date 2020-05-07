cmake_minimum_required(VERSION 3.5)

project(jmichkenger LANGUAGES CXX)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(Tests)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS thread system  regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_THREAD_LIBRARY}  ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


 add_executable(jmichkenger
    main.cpp
    chatlist/chatlist.cpp
    chatlist/chatlist.h
    custommbutton/custombutton.h
    custommbutton/custombutton.cpp
    datashowwidget/datashowwidget.cpp
    datashowwidget/datashowwidget.h
    profiledata/profiledata.h
    grouplist/grouplist.cpp
    grouplist/grouplist.h
    authwidget/authwidget.cpp
    authwidget/authwidget.h
    chatmodel.h
    chatmodel.cpp
    groupmodel.cpp
    groupmodel.h
    grouplistview.cpp
    grouplistview.h
    groupdelegate.cpp
    groupdelegate.h
    chatview.cpp
    chatview.h
    chatdelegate.cpp
    chatdelegate.h
    mainwidget.cpp
    mainwidget.h
    mainwidget.ui
    menuwidget.cpp
    menuwidget.h
    menuwidget.ui
    creategroupwidget.cpp
    creategroupwidget.h
    creategroupwidget.ui
    messageitemwidget.cpp
    messageitemwidget.h
    messageitemwidget.ui
    avatarbutton.cpp
    avatarbutton.h
    proxymodel.cpp
    proxymodel.h
    chatinput.cpp
    chatinput.h
    ../netlib/announcer/Announcer.cpp ../netlib/announcer/Announcer.h ../netlib/info/Info.cpp ../netlib/info/Info.h ../netlib/parser/Parser.cpp ../netlib/parser/Parser.h ../netlib/client/Client.cpp
    ../netlib/client/Client.h ../netlib/AppNetwork.cpp ../netlib/AppNetwork.h ../netlib/cache/Cache.cpp ../netlib/cache/Cache.h
 )


target_link_libraries(jmichkenger PRIVATE Qt5::Widgets ${USED_LIBS})
