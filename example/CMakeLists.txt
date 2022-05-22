add_executable(jemalloc-test jemalloc.cpp)

find_package(PkgConfig)
pkg_search_module(JEMALLOC jemalloc)

target_compile_options(jemalloc-test PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(jemalloc-test PRIVATE cxx_std_20)
target_link_libraries(jemalloc-test PRIVATE -lboost_unit_test_framework ${JEMALLOC_LIBRARIES})
target_include_directories(jemalloc-test PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${JEMALLOC_INCLUDE_DIRS}
)
