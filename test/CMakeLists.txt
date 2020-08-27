cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES
        ../include/ShivLib/matrix.hpp
        ../include/ShivLib/array.hpp ../include/ShivLib/vector.hpp)
set(TESTSRC
        matrixTest.cpp arrayTest.cpp vectorTest.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ShivLib ${INCLUDES} ${TESTSRC})
target_link_libraries(ShivLib -lboost_unit_test_framework)