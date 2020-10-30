#include "../include/ShivLib/dataStructures/vector.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vector_test) // NOLINT(cert-err58-cpp)
    BOOST_AUTO_TEST_CASE(range_based_test){ // NOLINT(cert-err58-cpp)

        //vector<int> vector1{2};

        //for(auto&& i: vector1){
        //    
        //}
    }
    
    BOOST_AUTO_TEST_CASE(adding_elements_test){ // NOLINT(cert-err58-cpp)

        ShivLib::vector<int> vector1(2);
        int a = 1;
        ShivLib::vector<int> vector1Expected{1, 2};
        vector1.push_back(a);
        vector1.emplace_back(2);
        BOOST_TEST(vector1 == vector1Expected);
        
        vector1.resize(20);
        BOOST_TEST(vector1.size() == 2U);
        BOOST_TEST(vector1.max_size() == 20U);
        BOOST_TEST(vector1.capacity() == 20U);
    }

    BOOST_AUTO_TEST_CASE(removing_elements_test){ // NOLINT(cert-err58-cpp)

        ShivLib::vector<int> vector1{2};
        ShivLib::vector<int> vector1Expected{1, 2};
        vector1.pop_back();
        BOOST_TEST(vector1 == vector1Expected);
        
        vector1.clear();
        BOOST_TEST(vector1.empty() == true);
    }

    BOOST_AUTO_TEST_CASE(iterator_test){ // NOLINT(cert-err58-cpp)

        ShivLib::vector<int> vector1{1, 0, 2, 3, 4};
        ShivLib::vector<int> vectorOrdered{0, 1, 2, 3, 4};
        ShivLib::vector<int> vectorReversed{4, 3, 2, 1, 0};
        
        BOOST_TEST((*std::find(vector1.cbegin(), vector1.cend(), 1)) == 1);
        BOOST_TEST((*std::find(vector1.crbegin(), vector1.crend(), 0)) == 0);
        std::sort(vector1.begin(), vector1.end());
        BOOST_TEST(vector1 == vectorOrdered);
        std::sort(vector1.rbegin(), vector1.rend());
        BOOST_TEST(vector1 == vectorReversed);
        for(auto&& i: vector1){
            i = 7;
        }
        BOOST_TEST(vector1[4] == 7);
    }
    
    BOOST_AUTO_TEST_CASE(access_test){ // NOLINT(cert-err58-cpp)

        ShivLib::vector<double> vector1{0, 1, 2, 3, 4};
        const ShivLib::vector<double> vector1Const{0, 1, 2, 3, 4};

        BOOST_TEST(vector1.at(2) == 2);
        BOOST_TEST(vector1Const.at(2) == 2);
        BOOST_TEST(vector1[3] == 3);
        BOOST_TEST(vector1Const[3] == 3);
        BOOST_TEST(vector1.front() == 0);
        BOOST_TEST(vector1Const.front() == 0);
        BOOST_TEST(vector1.back() == 4);
        BOOST_TEST(vector1Const.back() == 4);
    }

    BOOST_AUTO_TEST_CASE(fillswap_test){ // NOLINT(cert-err58-cpp)

        ShivLib::vector<int> vector1{0, 1, 2, 3, 4};
        ShivLib::vector<int> vector2{4, 3, 2, 1, 0};
        ShivLib::vector<int> expectedVector1{4, 3, 2, 1, 0};
        ShivLib::vector<int> expectedVector2{4, 4, 4, 4, 4};
        vector1.swap(vector2);

        BOOST_TEST(vector1 == expectedVector1);
        BOOST_TEST(vector2 != expectedVector1);
        vector2.fill(4);
        BOOST_TEST(vector2 == expectedVector2);
    }
BOOST_AUTO_TEST_SUITE_END() // NOLINT(cert-err58-cpp)