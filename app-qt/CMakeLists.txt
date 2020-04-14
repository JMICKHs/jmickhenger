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
    mainwindow.cpp
    mainwindow.h
    chatlist.cpp
    chatlist.h
    customButton.h
    custombutton.cpp
    menuwidget.cpp
    menuwidget.h
    datashowwidget.cpp
    datashowwidget.h
    profiledata.h
    grouplist.cpp
    grouplist.h
    authwidget.cpp
    authwidget.h
 )


target_link_libraries(jmichkenger PRIVATE Qt5::Widgets)
