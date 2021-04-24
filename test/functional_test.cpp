#include "../include/ShivLib/functional.hpp"
#include <functional>
#include <boost/test/unit_test.hpp>
int add(int a, int b){
    return a + b;
}
BOOST_AUTO_TEST_SUITE(functional_test)
    BOOST_AUTO_TEST_CASE(invoke_test){
        BOOST_TEST(shiv::invoke(add, 1, 3) == 4);
        std::tuple test{1, 3};
        BOOST_TEST(shiv::apply(add, test) == 4);
    }
BOOST_AUTO_TEST_SUITE_END()