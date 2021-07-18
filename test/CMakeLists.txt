cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TESTSRC
        matrix_test.cpp
        array_test.cpp
        vector_test.cpp
        string_view_test.cpp
        type_traits_test.cpp
        algorithm_test.cpp
        list_test.cpp
        lua_test.cpp
        functional_test.cpp
        utility_test.cpp)

set(EXPERIMENTAL
        experimental_test.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../Shivix-Standard-Library/include)

add_executable(ShivLib ${INCLUDES} ${TESTSRC} ${EXPERIMENTAL})
target_link_libraries(ShivLib -lboost_unit_test_framework -llua -ldl)
