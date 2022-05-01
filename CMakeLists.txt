cmake_minimum_required(VERSION 3.16)
project(ShivLib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDES
    include/ShivLib/dataStructures/array.hpp
    include/ShivLib/dataStructures/list.hpp
    include/ShivLib/dataStructures/matrix.hpp
    include/ShivLib/dataStructures/string.hpp
    include/ShivLib/dataStructures/string_view.hpp
    include/ShivLib/dataStructures/vector.hpp
    include/ShivLib/multithreading/mutex.hpp
    include/ShivLib/multithreading/thread.hpp
    include/ShivLib/algorithm.hpp
    include/ShivLib/cstddef.hpp
    include/ShivLib/exception.hpp
    include/ShivLib/iterators.hpp
    include/ShivLib/memory.hpp
    include/ShivLib/typeTraits.hpp
    include/ShivLib/utility.hpp
)

set(TESTSRC
    test/matrix_test.cpp
    test/array_test.cpp
    test/vector_test.cpp
    test/string_view_test.cpp
    test/type_traits_test.cpp
    test/algorithm_test.cpp
    test/functional_test.cpp
    test/utility_test.cpp
)

set(EXPERIMENTAL
	include/ShivLib/experimental/lazy_evaluation.hpp
	include/ShivLib/experimental/ranges.hpp
    test/experimental_test.cpp
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
enable_testing()
add_executable(shiv-test ${TESTSRC} ${EXPERIMENTAL})
target_link_libraries(shiv-test -lboost_unit_test_framework -llua -ldl)
target_include_directories(shiv-test PRIVATE include)
add_test(ShivTest shiv-test)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)
    add_custom_target(clang-format COMMAND clang-format -i ${SOURCE_FILES})
endif()

