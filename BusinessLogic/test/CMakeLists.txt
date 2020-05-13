set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)

find_package (Boost REQUIRED)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
link_directories(${LIBMONGOCXX_INCLUDE_DIRS})
link_directories(${LIBBSONCXX_INCLUDE_DIR})
link_directories(${Boost_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/Business-Logic" "${PROJECT_SOURCE_DIR}/DBWorker" "${PROJECT_SOURCE_DIR}/Services" "${PROJECT_SOURCE_DIR}/JsonParser" "${PROJECT_SOURCE_DIR}/SupportStructures")

file(GLOB sources "${PROJECT_SOURCE_DIR}/Business-Logic/*.cpp" "${PROJECT_SOURCE_DIR}/DBWorker/*.cpp" "${PROJECT_SOURCE_DIR}/Services/*.cpp" "${PROJECT_SOURCE_DIR}/JsonParser/*.cpp" "${PROJECT_SOURCE_DIR}/SupportStructures/*.cpp")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}//BusinessLogic/main.cpp")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main_test.cpp")
    target_link_libraries("${name}_tests" gtest_main gmock_main ${LIBMONGOCXX_LIBRARIES} ${lIBBSONCXX_LIBRARIES} ${Boost_LIBRARIES})
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
