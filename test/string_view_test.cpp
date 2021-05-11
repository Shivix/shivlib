#include <ShivLib/dataStructures/string_view.hpp>
#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(string_view_test)
BOOST_AUTO_TEST_CASE(trim_test){
    std::string test_string{"    Hello, world  "};
    shiv::string_view test_view{test_string};
    test_view.remove_prefix(4);
    test_view.remove_suffix(2);
    BOOST_TEST(test_view == shiv::string_view("Hello, world"));
}
BOOST_AUTO_TEST_SUITE_END()