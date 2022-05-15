cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(shivlib INTERFACE)
target_compile_features(shivlib INTERFACE cxx_std_20)

add_subdirectory(test)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE CPP_FILES *.cpp *.hpp)
    add_custom_target(clang-format COMMAND clang-format -i ${CPP_FILES})
endif()
