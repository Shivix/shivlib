#include "../include/ShivLib/vector.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vector_test) // NOLINT(cert-err58-cpp)
    BOOST_AUTO_TEST_CASE(range_based_test){ // NOLINT(cert-err58-cpp)

        //vector<int> vector1{2};

        //for(auto&& i: vector1){
        //    
        //}
    }
    
    BOOST_AUTO_TEST_CASE(adding_elements_test){ // NOLINT(cert-err58-cpp)

        vector<int> vector1{2};
        int a = 1;
        vector<int> vector1Expected{1, 2};
        vector1.push_back(a);
        vector1.emplace_back(2);
        BOOST_TEST(vector1 == vector1Expected);
        
        vector1.resize(20);
        BOOST_TEST(vector1.size() == 20);
    }

    BOOST_AUTO_TEST_CASE(removing_elements_test){ // NOLINT(cert-err58-cpp)

        vector<int> vector1{2};
        vector<int> vector1Expected{1, 2};
        vector1.pop_back();
        BOOST_TEST(vector1 == vector1Expected);
        
        vector1.clear();
        BOOST_TEST(vector1.empty() == true);
        
        vector1.resize(20);
        BOOST_TEST(vector1.size() == 20);
    }
BOOST_AUTO_TEST_SUITE_END() // NOLINT(cert-err58-cpp)