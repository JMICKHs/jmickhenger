INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
set(SOURCE_FILES  ../mainwindow.cpp
    ../custombutton.cpp
    ../grouplist.cpp
    ../menuwidget.cpp
    ../chatlist.cpp
    ../datashowwidget.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

 add_executable(Tests
     test_chat.cpp
     test_group.cpp
     main.cpp
     test_chat.h
     test_group.h
     test_showprofile.cpp
     test_showprofile.h
     ${SOURCE_FILES}
    )
add_test(NAME test_chat COMMAND test_chat)
add_test(NAME test_group COMMAND test_group)

target_link_libraries(Tests PRIVATE Qt5::Widgets Qt5::Test)
