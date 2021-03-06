cmake_minimum_required(VERSION 3.10)

set(SOURCE_FILES
    ../app-qt/src/chatinput/chatinput.cpp
    ../app-qt/src/creategroup/creategroupwidget.cpp
    ../app-qt/src/custommbutton/custombutton.cpp
    ../app-qt/src/delegates/chatdelegate.cpp
    ../app-qt/src/delegates/groupdelegate.cpp
    ../app-qt/src/delegates/friendsdelegate.cpp
    ../app-qt/src/mainwidget/mainwidget.cpp
    ../app-qt/src/menuwidget/menuwidget.cpp
    ../app-qt/src/models/chatmodel.cpp
    ../app-qt/src/models/groupmodel.cpp
    ../app-qt/src/proxy/proxymodel.cpp
    ../app-qt/src/proxy/friendmodelproxy.cpp
    ../app-qt/src/views/chatview.cpp
    ../app-qt/src/views/grouplistview.cpp
    ../app-qt/src/loginwidget/loginwidget.cpp
    ../app-qt/src/models/usermodel.cpp
    ../app-qt/src/custominputforms/custominputforms.cpp
    ../app-qt/src/mainlogic/mainlogic.cpp
    ../app-qt/src/models/friendsmodel.cpp
    ../app-qt/src/views/friendsview.cpp
    ../app-qt/src/setavatarwidget/setavatarwidget.cpp
    ../app-qt/src/addfriendwidget/addfriendwidget.cpp
    ../netlib/info/Info.cpp
    ../netlib/cache/Cache.cpp
    ../netlib/client/Client.cpp
    ../netlib/parser/Parser.cpp
    ../netlib/announcer/Announcer.cpp
    ../netlib/AppNetwork.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets  REQUIRED)
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


add_executable(Tests
     test_chat.cpp
     test_group.cpp
     main.cpp
     test_chat.h
     test_group.h
     test_showprofile.cpp
     test_showprofile.h
     test_client.cpp
     ${SOURCE_FILES}
    )
add_test(NAME test_chat COMMAND test_chat)
add_test(NAME test_group COMMAND test_group)

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/Tests/main.cpp")
    target_link_libraries("${name}_tests" gtest_main)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()

target_link_libraries(Tests PRIVATE Qt5::Widgets Qt5::Test gtest_main gmock_main ${USED_LIBS})
