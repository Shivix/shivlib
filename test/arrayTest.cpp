#include "../include/ShivLib/array.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(array_iterator_test) // NOLINT
{
    
}

BOOST_AUTO_TEST_CASE(fillswap_test) // NOLINT
{
    ShivLib::array<int, 5> array1{0, 1, 2, 3, 4};
    ShivLib::array<int, 5> array2{4, 3, 2, 1, 0};
    ShivLib::array<int, 5> expectedArray1{4, 4, 4, 4, 4};
    array1.swap(array2);
    
    BOOST_TEST(array1 == array2);
    array2.fill(4);
    BOOST_TEST(array2 == expectedArray1);
}