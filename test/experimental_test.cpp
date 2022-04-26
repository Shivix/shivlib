#include <ShivLib/experimental/lazy_evaluation.hpp>
#include <ShivLib/experimental/ranges.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

BOOST_AUTO_TEST_SUITE(experimental_test)
    BOOST_AUTO_TEST_CASE(range_test){ 
        for(auto&& i: range(0, 10)){
            std::cout << i;
        }
    }
    
    BOOST_AUTO_TEST_CASE(lazy_test){
        int a{50};
        shiv::lazyEvaluation<int> lazy_int{[a](){
                return a * std::sqrt(100) / a;
            }};
        BOOST_TEST(lazy_int.get() == 10);
    }
BOOST_AUTO_TEST_SUITE_END()
