cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(shiv-test
    test/array_test.cpp
    test/algorithm_test.cpp
    test/experimental_test.cpp
    test/functional_test.cpp
    test/matrix_test.cpp
    test/string_view_test.cpp
    test/type_traits_test.cpp
    test/utility_test.cpp
    test/vector_test.cpp
)

find_package(Boost REQUIRED COMPONENTS system)
enable_testing()

target_link_libraries(shiv-test -lboost_unit_test_framework -llua -ldl)
target_include_directories(shiv-test PRIVATE include ${Boost_INCLUDE_DIRS})
add_test(ShivTest shiv-test)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)
    add_custom_target(clang-format COMMAND clang-format -i ${SOURCE_FILES})
endif()

