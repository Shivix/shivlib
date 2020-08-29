#include "../include/ShivLib/array.hpp"
#include <boost/test/unit_test.hpp>

// Using auto test suite for now since it builds alot faster as we get more tests,
// suite will be create manually for better output
BOOST_AUTO_TEST_SUITE(array_test) // NOLINT(cert-err58-cpp)
    BOOST_AUTO_TEST_CASE(array_iterator_test){ // NOLINT(cert-err58-cpp)
    
        ShivLib::array<int, 5> array1{1, 0, 2, 3, 4};
        ShivLib::array<int, 5> arrayOrdered{0, 1, 2, 3, 4};
        ShivLib::array<int, 5> arrayReversed{4, 3, 2, 1, 0};


        BOOST_TEST((*std::find(array1.cbegin(), array1.cend(), 1)) == 1);
        BOOST_TEST((*std::find(array1.crbegin(), array1.crend(), 0)) == 0);
        std::sort(array1.begin(), array1.end());
        BOOST_TEST(array1 == arrayOrdered);
        std::sort(array1.rbegin(), array1.rend());
        BOOST_TEST(array1 == arrayReversed);
        for(auto&& i: array1){
            i = 7;
        }
        BOOST_TEST(array1[4] == 7);
    }

    BOOST_AUTO_TEST_CASE(fillswap_test){ // NOLINT(cert-err58-cpp)
    
        ShivLib::array<int, 5> array1{0, 1, 2, 3, 4};
        ShivLib::array<int, 5> array2{4, 3, 2, 1, 0};
        ShivLib::array<int, 5> expectedArray1{4, 3, 2, 1, 0};
        ShivLib::array<int, 5> expectedArray2{4, 4, 4, 4, 4};
        array1.swap(array2);

        BOOST_TEST(array1 == expectedArray1);
        BOOST_TEST(array2 != expectedArray1);
        array2.fill(4);
        BOOST_TEST(array2 == expectedArray2);
    }

    BOOST_AUTO_TEST_CASE(capacity_test){ // NOLINT(cert-err58-cpp)
    
        ShivLib::array<int, 5> array1{0, 1, 2, 3, 4};
        BOOST_TEST(array1.size() == std::size_t(5));
        BOOST_TEST(array1.max_size() == std::size_t(5));
        ShivLib::array<int, 0> array2{};
        BOOST_TEST(array2.empty() == true);
        BOOST_TEST(array1.empty() == false);
    }

    BOOST_AUTO_TEST_CASE(access_test){ // NOLINT(cert-err58-cpp)
    
        ShivLib::array<int, 5> array1{0, 1, 2, 3, 4};
        const ShivLib::array<int, 5> array1Const{0, 1, 2, 3, 4};
        
        BOOST_TEST(array1.at(2) == 2);
        BOOST_TEST(array1Const.at(2) == 2);
        BOOST_TEST(array1[3] == 3);
        BOOST_TEST(array1Const[3] == 3);
        BOOST_TEST(array1.front() == 0);
        BOOST_TEST(array1Const.front() == 0);
        BOOST_TEST(array1.back() == 4);
        BOOST_TEST(array1Const.back() == 4);
    }

    BOOST_AUTO_TEST_CASE(zero_sized_test){ // NOLINT(cert-err58-cpp)

        [[maybe_unused]] ShivLib::array<int, 0> array1{};
        
        //BOOST_TEST(array1.at(2) == 2);
        //BOOST_TEST(array1[3] == 3);
        
    }
BOOST_AUTO_TEST_SUITE_END() // NOLINT(cert-err58-cpp)