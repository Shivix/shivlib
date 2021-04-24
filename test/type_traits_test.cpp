#include "../include/ShivLib/type_traits.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(type_trait_test)
    BOOST_AUTO_TEST_CASE(type_trait_remove_qualifier_test){
    
        int&& ref1 = 5;
        BOOST_TEST(shiv::is_reference_v<shiv::remove_reference_t<decltype(ref1)>> == false);

        [[maybe_unused]] shiv::remove_cv_t<const volatile int> cvint1;
        [[maybe_unused]] int int1;
        bool result = shiv::is_same<decltype(cvint1), decltype(int1)>::value;
        BOOST_TEST(result == true);
    }
    
    BOOST_AUTO_TEST_CASE(type_trait_remove_conditional_test){

        shiv::enable_if<true, int>::type int1 = 1;
        
        BOOST_TEST(int1 == 1);
    }

    BOOST_AUTO_TEST_CASE(type_trait_type_check_test){

        shiv::is_array<int[5]> array1;
        shiv::is_array<int> notArray1;

        BOOST_TEST(array1 == true);
        BOOST_TEST(notArray1 == false);
        
        BOOST_TEST(shiv::is_arithmetic_v<float>  == true);
        BOOST_TEST(shiv::is_arithmetic_v<void>  == false);
    }
BOOST_AUTO_TEST_SUITE_END()