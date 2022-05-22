#include <ShivLib/dataStructures/array.hpp>
#include <boost/test/unit_test.hpp>

// Using auto test suite for now since it builds alot faster as we get more tests,
// suite will be create manually for better output
BOOST_AUTO_TEST_SUITE(array_test)
BOOST_AUTO_TEST_CASE(array_iterator_test) {
    shiv::Array<int, 5> array1{1, 0, 2, 3, 4};
    shiv::Array<int, 5> array_ordered{0, 1, 2, 3, 4};
    shiv::Array<int, 5> array_reversed{4, 3, 2, 1, 0};

    BOOST_TEST((*std::find(array1.cbegin(), array1.cend(), 1)) == 1);
    BOOST_TEST((*std::find(array1.crbegin(), array1.crend(), 0)) == 0);
    std::sort(array1.begin(), array1.end());
    BOOST_TEST(array1 == array_ordered);
    std::sort(array1.rbegin(), array1.rend());
    BOOST_TEST(array1 == array_reversed);
    for (auto&& i : array1) {
        i = 7;
    }
    BOOST_TEST(array1[4] == 7);
}

BOOST_AUTO_TEST_CASE(fillswap_test) {
    shiv::Array<int, 5> array1{0, 1, 2, 3, 4};
    shiv::Array<int, 5> array2{4, 3, 2, 1, 0};
    shiv::Array<int, 5> expected_array1{4, 3, 2, 1, 0};
    shiv::Array<int, 5> expected_array2{4, 4, 4, 4, 4};
    array1.swap(array2);

    BOOST_TEST(array1 == expected_array1);
    BOOST_TEST(array2 != expected_array1);
    array2.fill(4);
    BOOST_TEST(array2 == expected_array2);
}

BOOST_AUTO_TEST_CASE(capacity_test) {
    shiv::Array<int, 5> array1{0, 1, 2, 3, 4};
    BOOST_TEST(array1.size() == std::size_t{5});
    BOOST_TEST(array1.max_size() == std::size_t{5});
    shiv::Array<int, 0> array2{};
    BOOST_TEST(array2.empty() == true);
    BOOST_TEST(array1.empty() == false);
}

BOOST_AUTO_TEST_CASE(access_test) {
    shiv::Array<int, 5> array1{0, 1, 2, 3, 4};
    const shiv::Array<int, 5> array1_const{0, 1, 2, 3, 4};

    BOOST_TEST(array1.at(2) == 2);
    BOOST_TEST(array1_const.at(2) == 2);
    BOOST_TEST(array1[3] == 3);
    BOOST_TEST(array1_const[3] == 3);
    BOOST_TEST(array1.front() == 0);
    BOOST_TEST(array1_const.front() == 0);
    BOOST_TEST(array1.back() == 4);
    BOOST_TEST(array1_const.back() == 4);
}

BOOST_AUTO_TEST_CASE(zero_sized_test) {
    shiv::Array<int, 0> array1{};

    BOOST_TEST(array1.empty() == true);
    BOOST_CHECK_THROW(std::ignore = array1.front(), std::out_of_range);
}
BOOST_AUTO_TEST_CASE(comparison_test) {
    shiv::Array<int, 5> array1{1, 2, 3, 4, 5};
    shiv::Array<int, 5> array2{1, 2, 3, 4, 5};
    shiv::Array<int, 5> array_lt{0, 1, 2, 3, 4};
    shiv::Array<int, 5> array_gt{2, 3, 4, 5, 6};
    BOOST_TEST(array1 == array2);
    BOOST_TEST(array1 != array_lt);
    BOOST_TEST(array1 > array_lt);
    BOOST_TEST(array1 < array_gt);
}
BOOST_AUTO_TEST_SUITE_END()
