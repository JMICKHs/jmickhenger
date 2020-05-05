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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

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
 )


target_link_libraries(jmichkenger PRIVATE Qt5::Widgets)
