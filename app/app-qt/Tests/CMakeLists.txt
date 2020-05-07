INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
set(SOURCE_FILES
    ../custommbutton/custombutton.cpp
    ../grouplist/grouplist.cpp
    ../chatlist/chatlist.cpp
    ../datashowwidget/datashowwidget.cpp
    ../authwidget/authwidget.cpp
    ../chatmodel.cpp
    ../groupmodel.cpp
    ../grouplistview.cpp
    ../groupdelegate.cpp
    ../chatview.cpp
    ../chatdelegate.cpp
    ../menuwidget.cpp
    ../mainwidget.cpp
    ../creategroupwidget.cpp
    ../messageitemwidget.cpp
    ../avatarbutton.cpp
    ../proxymodel.cpp
    ../chatinput.cpp
    ../netlib/announcer/Announcer.cpp
    ../netlib/info/Info.cpp
    ../netlib/parser/Parser.cpp
    ../netlib/client/Client.cpp
    ../netlib/AppNetwork.cpp
    ../netlib/cache/Cache.cpp
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets  REQUIRED)

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
