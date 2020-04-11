INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
set(SOURCE_FILES  ../mainwindow.cpp
    ../custombutton.cpp
    ../grouplistitem.cpp
    ../grouplistobject.cpp
    ../menuwidget.cpp
    ../chatlist.cpp)

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
     ${SOURCE_FILES}
    )

target_link_libraries(Tests PRIVATE Qt5::Widgets Qt5::Test)
