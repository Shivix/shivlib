#include "../include/ShivLib/algorithm.hpp"
#include "../include/ShivLib/dataStructures/array.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(algorithm_test)
BOOST_AUTO_TEST_CASE(comparitor_test){
    auto test = shiv::min(3, 8);
    BOOST_TEST(shiv::max(5, 8) == 8);
    BOOST_TEST(test == 3);
    shiv::array<int, 3> test_array{0, 1, 2};
    shiv::array<int, 3> test_array_2{1, 2, 3};
    BOOST_TEST(shiv::equal(test_array.begin(), test_array.end(), test_array_2.begin()) == false);
    shiv::array<int, 3> test_array_3{0, 1, 2};
    shiv::array<int, 3> test_array_4{0, 1, 2};
    BOOST_TEST(shiv::equal(test_array_3.begin(), test_array_3.end(), test_array_4.begin()) == true);
}
BOOST_AUTO_TEST_SUITE_END()