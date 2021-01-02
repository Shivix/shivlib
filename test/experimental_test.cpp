#include "../include/ShivLib/experimental/lazy_evaluation.hpp"
#include "../include/ShivLib/experimental/ranges.hpp"
#include <boost/test/unit_test.hpp>
#include <cmath>

BOOST_AUTO_TEST_SUITE(experimental_test) // NOLINT(cert-err58-cpp)
    BOOST_AUTO_TEST_CASE(range_test){ // NOLINT(cert-err58-cpp) 
        for(auto&& i: range(0, 10)){
            std::cout << i;
        }
    }
    
    BOOST_AUTO_TEST_CASE(lazy_test){ // NOLINT(cert-err58-cpp
        int a{50};
        shiv::lazyEvaluation<int> lazy_int{[a](){
                return a * std::sqrt(100) / a;
            }};
        BOOST_TEST(lazy_int.get() == 10);
    }
BOOST_AUTO_TEST_SUITE_END()