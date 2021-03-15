cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDES
        ../include/ShivLib/dataStructures/array.hpp
        ../include/ShivLib/dataStructures/matrix.hpp
        ../include/ShivLib/dataStructures/map.hpp
        ../include/ShivLib/dataStructures/string.hpp
        ../include/ShivLib/dataStructures/string_view.hpp 
        ../include/ShivLib/dataStructures/vector.hpp
        ../include/ShivLib/dataStructures/list.hpp
        ../include/ShivLib/multithreading/mutex.hpp
        ../include/ShivLib/multithreading/thread.hpp
        ../include/ShivLib/algorithm.hpp
        ../include/ShivLib/exception.hpp
        ../include/ShivLib/utility.hpp
        ../include/ShivLib/type_traits.hpp
        ../include/ShivLib/memory.hpp
        ../include/ShivLib/cstddef.hpp
        ../include/ShivLib/iterators.hpp
        ../include/ShivLib/concepts.hpp) 

set(TESTSRC
        matrix_test.cpp
        array_test.cpp
        vector_test.cpp
        type_traits_test.cpp
        algorithm_test.cpp
        list_test.cpp
        lua_test.cpp)

set(EXPERIMENTAL
        ../include/ShivLib/experimental experimental_test.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ShivLib ${INCLUDES} ${TESTSRC} ${EXPERIMENTAL})
target_link_libraries(ShivLib -lboost_unit_test_framework -llua -ldl)