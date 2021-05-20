#include <ShivLib/dataStructures/string_view.hpp>
#include <boost/test/unit_test.hpp>
#include <string>
#include <string_view>

BOOST_AUTO_TEST_SUITE(string_view_test)
BOOST_AUTO_TEST_CASE(trim_test){
    std::string test_string{"    Hello, world  "};
    shiv::string_view test_view{test_string};
    test_view.remove_prefix(4);
    test_view.remove_suffix(2);
    BOOST_TEST(test_view == shiv::string_view("Hello, world"));
}

BOOST_AUTO_TEST_CASE(substr_test){
    std::string test_string{"Hello, world"};
    shiv::string_view test_view{test_string};
    BOOST_TEST(test_view.substr(0, 5) == shiv::string_view("Hello"));
    BOOST_TEST(test_view.substr(7, 5) == shiv::string_view("world"));
}

BOOST_AUTO_TEST_CASE(x_with_test){
    shiv::string_view test_view{"Hello, world"};
    shiv::string_view end_view{"world"};
    BOOST_TEST(test_view.starts_with("Hello"));
    BOOST_TEST(test_view.ends_with("world"));
    BOOST_TEST(!test_view.ends_with("Hello"));
    BOOST_TEST(test_view.ends_with(end_view));
    BOOST_TEST(test_view.starts_with('H'));
}

BOOST_AUTO_TEST_CASE(comparison_test){
    shiv::string_view shiv_view{"hello, world"};
    shiv::string_view shiv_view2{"zzzzzzzzz"};
	std::string_view std_view{"hello, world"};
	std::string_view std_view2{"zzzzzzzzz"};
	BOOST_TEST(shiv_view.compare(shiv_view2) == std_view.compare(std_view2));
	BOOST_TEST(shiv_view2.compare("zzzzzzzzz") == 0);
	BOOST_TEST(shiv_view2.compare("zzzzzzzzzzzz") == -3);
	BOOST_TEST(shiv_view.compare(7, 5, shiv::string_view("world")) == 0);
	BOOST_TEST(shiv_view.compare(7, 5, shiv::string_view("zzzworld"), 3, 5) == 0);
}
BOOST_AUTO_TEST_SUITE_END()
