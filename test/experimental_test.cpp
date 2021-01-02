#include "../include/ShivLib/experimental/ranges.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(experimental_test) // NOLINT(cert-err58-cpp)
    BOOST_AUTO_TEST_CASE(range_test){ // NOLINT(cert-err58-cpp) 
        for(auto&& i: range(0, 10)){
            std::cout << i;
        }
    }
BOOST_AUTO_TEST_SUITE_END()