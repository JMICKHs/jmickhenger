include_directories("${PROJECT_SOURCE_DIR}/netlib")

file(GLOB netLib
        "${PROJECT_SOURCE_DIR}/netlib/*.cpp"
        "${PROJECT_SOURCE_DIR}/netlib/*/*.cpp"
        "${PROJECT_SOURCE_DIR}/netlib/*.h"
        "${PROJECT_SOURCE_DIR}/netlib/*/*.h")


#add_directory("${PROJECT_SOURCE_DIR}/netlib")

file(GLOB tests "${PROJECT_SOURCE_DIR}/tests-netlib/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests-netlib/main.cpp")


find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${netLib}
            ${file}
            "${PROJECT_SOURCE_DIR}/tests-netlib/main.cpp")
    target_link_libraries("${name}_tests" gtest_main)
    target_link_libraries("${name}_tests" ${Boost_LIBRARIES})
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()