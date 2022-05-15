add_executable(shiv-test
    array_test.cpp
    algorithm_test.cpp
    experimental_test.cpp
    functional_test.cpp
    matrix_test.cpp
    string_view_test.cpp
    type_traits_test.cpp
    utility_test.cpp
    vector_test.cpp
)

find_package(Boost REQUIRED COMPONENTS system)

enable_testing()

target_compile_options(shiv-test PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(shiv-test PRIVATE cxx_std_20)
target_link_libraries(shiv-test PRIVATE -lboost_unit_test_framework)
target_include_directories(shiv-test PRIVATE ../include ${Boost_INCLUDE_DIRS})

add_test(ShivTest shiv-test)
