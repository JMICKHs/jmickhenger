cmake_minimum_required(VERSION 3.10)

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
add_subdirectory(netlib)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.67.0 REQUIRED COMPONENTS thread system  regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_THREAD_LIBRARY}  ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread")

add_executable(jmichkenger
     app-qt/src/chatinput/chatinput.h
     app-qt/src/chatinput/chatinput.cpp
     app-qt/src/creategroup/creategroupwidget.cpp
     app-qt/src/creategroup/creategroupwidget.h
     app-qt/src/custommbutton/custombutton.cpp
     app-qt/src/custommbutton/custombutton.h
     app-qt/src/delegates/chatdelegate.cpp
     app-qt/src/delegates/chatdelegate.h
     app-qt/src/delegates/groupdelegate.cpp
     app-qt/src/delegates/groupdelegate.h
     app-qt/src/mainwidget/mainwidget.cpp
     app-qt/src/mainwidget/mainwidget.h
     app-qt/src/menuwidget/menuwidget.cpp
     app-qt/src/menuwidget/menuwidget.h
     app-qt/src/models/chatmodel.cpp
     app-qt/src/models/chatmodel.h
     app-qt/src/models/groupmodel.h
     app-qt/src/models/groupmodel.cpp
     app-qt/src/proxy/proxymodel.cpp
     app-qt/src/proxy/proxymodel.h
     app-qt/src/views/chatview.cpp
     app-qt/src/views/chatview.h
     app-qt/src/views/grouplistview.cpp
     app-qt/src/views/grouplistview.h
     app-qt/src/creategroup/creategroupwidget.ui
     app-qt/src/mainwidget/mainwidget.ui
     app-qt/src/menuwidget/menuwidget.ui
     app-qt/src/loginwidget/loginwidget.cpp
     app-qt/src/loginwidget/loginwidget.h
     app-qt/src/loginwidget/loginwidget.ui
     app-qt/src/models/usermodel.h
     app-qt/src/models/usermodel.cpp
     app-qt/src/custominputforms/custominputforms.h
     app-qt/src/custominputforms/custominputforms.cpp
     app-qt/src/mainlogic/mainlogic.cpp
     app-qt/src/mainlogic/mainlogic.h
     app-qt/src/models/friendsmodel.cpp
     app-qt/src/models/friendsmodel.h
     app-qt/src/views/friendsview.cpp
     app-qt/src/views/friendsview.h
     main.cpp
 )
target_link_libraries(jmichkenger PRIVATE Qt5::Widgets ${USED_LIBS} netlib)
target_link_libraries(netlib ${USET_LIBS})
