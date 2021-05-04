#include "../include/ShivLib/utility.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vector_test)
    BOOST_AUTO_TEST_CASE(move_test) {
        struct Test {
            int a{5};
            Test() = default;
            Test(Test&&) noexcept(false) {
                throw 5;
            };
        };
        Test test0;
        //auto noexcept_test{shiv::move_if_noexcept(test0)};
    }
BOOST_AUTO_TEST_SUITE_END()