cmake_minimum_required(VERSION 3.5)

project(jmichkenger LANGUAGES CXX)

enable_testing()
add_subdirectory(Tests)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

 add_executable(jmichkenger
    main.cpp
    mainwindow.cpp
    mainwindow.h
    grouplistobject.h
    grouplistobject.cpp
    chatlist.cpp
    chatlist.h
    customButton.h
    custombutton.cpp
    menuwidget.cpp
    menuwidget.h
    grouplistitem.cpp
    grouplistitem.h
    datashowwidget.cpp
    datashowwidget.h
    profiledata.h
 )


target_link_libraries(jmichkenger PRIVATE Qt5::Widgets)
