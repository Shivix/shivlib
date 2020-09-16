cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES
        include/ShivLib/dataStructures/matrix.hpp
        include/ShivLib/dataStructures/array.hpp)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_library(ShivLib INTERFACE)