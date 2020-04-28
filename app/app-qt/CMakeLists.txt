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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

 add_executable(jmichkenger
    main.cpp
    mainwindow/mainwindow.cpp
    mainwindow/mainwindow.h
    chatlist/chatlist.cpp
    chatlist/chatlist.h
    custommbutton/customButton.h
    custommbutton/custombutton.cpp
    menuwidget/menuwidget.cpp
    menuwidget/menuwidget.h
    datashowwidget/datashowwidget.cpp
    datashowwidget/datashowwidget.h
    profiledata/profiledata.h
    grouplist/grouplist.cpp
    grouplist/grouplist.h
    authwidget/authwidget.cpp
    authwidget/authwidget.h
 )


target_link_libraries(jmichkenger PRIVATE Qt5::Widgets)
