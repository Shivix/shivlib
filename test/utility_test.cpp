#include <ShivLib/utility.hpp>
#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_SUITE(vector_test)
    BOOST_AUTO_TEST_CASE(move_test) {
        struct Test {
            Test() = default;
            Test(const Test&) = default;
            Test(Test&&) noexcept(true){
            };
        };
        Test test0{};
        [[maybe_unused]] decltype(auto) noexcept_test{shiv::move_if_noexcept(test0)};
    }
BOOST_AUTO_TEST_SUITE_END()