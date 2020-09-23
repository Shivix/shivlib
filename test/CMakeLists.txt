cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES
        ../include/ShivLib/dataStructures/array.hpp
        ../include/ShivLib/dataStructures/matrix.hpp
        ../include/ShivLib/dataStructures/map.hpp
        ../include/ShivLib/dataStructures/string.hpp
        ../include/ShivLib/dataStructures/vector.hpp
        ../include/ShivLib/multithreading/mutex.hpp
        ../include/ShivLib/multithreading/thread.hpp
        ../include/ShivLib/algorithm.hpp
        ../include/ShivLib/exception.hpp
        ../include/ShivLib/utility.hpp
        ../include/ShivLib/typeTraits.hpp
        ../include/ShivLib/memory.hpp
        ../include/ShivLib/cstddef.hpp
        ../include/ShivLib/iterators.hpp)

set(TESTSRC
        matrixTest.cpp
        arrayTest.cpp
        vectorTest.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ShivLib ${INCLUDES} ${TESTSRC})
target_link_libraries(ShivLib -lboost_unit_test_framework)