#include "../include/ShivLib/dataStructures/vector.hpp"
#include "../include/ShivLib/utility.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(vector_test)
    BOOST_AUTO_TEST_CASE(range_based_test){
        constexpr shiv::vector<int> test{};
        shiv::vector<int> vector1{0, 1, 2, 3, 4, 5};

        for(auto&& i: vector1){
            std::cout << i;
        }
    }
    
    BOOST_AUTO_TEST_CASE(constructor_test){
        shiv::vector<int> vector1{1, 2, 3};
        auto copied_vector{vector1};
        BOOST_TEST(copied_vector == vector1);
        shiv::vector<int> vector2{1, 2, 3, 4};
        shiv::vector<int> assigned_vector{};
        assigned_vector = vector2;
        BOOST_TEST(assigned_vector == vector2);

        shiv::vector<int> vector3{1, 2, 3};
        shiv::vector<int> expected{1, 2, 3};
        auto moved_vector{shiv::move(vector3)};
        BOOST_TEST(moved_vector == expected);
    } 
    
    BOOST_AUTO_TEST_CASE(adding_elements_test){
        shiv::vector<int> vector1(2);
        int a{1};
        shiv::vector<int> vector1Expected{1, 8, 5, 5, 2};
        vector1.push_back(a);
        vector1.push_back(5);
        vector1.emplace_back(2);
        int b{5};
        vector1.emplace(vector1.end() - 2, 8);
        vector1.insert(vector1.end() - 2, b);
        BOOST_TEST(vector1 == vector1Expected);
        vector1.insert(vector1.end() - 1, {0, 0, 0});
        shiv::vector<int> vector2Expected{1, 8, 5, 5, 0, 0, 0, 2};
        BOOST_TEST(vector1 == vector2Expected);
        vector1.insert(vector1.end() - 4, 3, 1);
        shiv::vector<int> vector3Expected{1, 8, 5, 5, 1, 1, 1, 0, 0, 0, 2};
        BOOST_TEST(vector1 == vector3Expected);
        vector1.resize(100);
        BOOST_TEST(vector1.size() == 11U);
        BOOST_TEST(vector1.max_size() == 100U);
        BOOST_TEST(vector1.capacity() == 100U);
    }

    BOOST_AUTO_TEST_CASE(removing_elements_test){
        shiv::vector<int> vector1{1, 2, 3};
        shiv::vector<int> vector1Expected{1, 2};
        vector1.pop_back();
        BOOST_TEST(vector1 == vector1Expected);
        BOOST_TEST(vector1.size() == 2);
        
        vector1.clear();
        BOOST_TEST(vector1.empty() == true);
        
        shiv::vector<int> vector2{1, 2, 3};
        vector2.reserve(32);
        vector2.shrink_to_fit();
        BOOST_TEST(vector2.capacity() == 3);
    }

    BOOST_AUTO_TEST_CASE(iterator_test){
        shiv::vector<int> vector1{1, 0, 2, 3, 4};
        shiv::vector<int> vectorOrdered{0, 1, 2, 3, 4};
        shiv::vector<int> vectorReversed{4, 3, 2, 1, 0};
        
        BOOST_TEST((*std::find(vector1.cbegin(), vector1.cend(), 1)) == 1);
        BOOST_TEST((*std::find(vector1.crbegin(), vector1.crend(), 0)) == 0);
        std::sort(vector1.begin(), vector1.end());
        BOOST_TEST(vector1 == vectorOrdered);
        std::sort(vector1.rbegin(), vector1.rend());
        BOOST_TEST(vector1 == vectorReversed);
        for(auto&& i: vector1){
            i = 7;
        }
        BOOST_TEST(vector1[4] == 7);
    }
    
    BOOST_AUTO_TEST_CASE(access_test){
        shiv::vector<double> vector1{0, 1, 2, 3, 4};
        const shiv::vector<double> vector1Const{0, 1, 2, 3, 4};

        BOOST_TEST(vector1.at(2) == 2);
        BOOST_TEST(vector1Const.at(2) == 2);
        BOOST_TEST(vector1[3] == 3);
        BOOST_TEST(vector1Const[3] == 3);
        BOOST_TEST(vector1.front() == 0);
        BOOST_TEST(vector1Const.front() == 0);
        BOOST_TEST(vector1.back() == 4);
        BOOST_TEST(vector1Const.back() == 4);
    }

    BOOST_AUTO_TEST_CASE(fillswap_test){
        shiv::vector<int> vector1{0, 1, 2, 3, 4};
        shiv::vector<int> vector2{4, 3, 2, 1};
        shiv::vector<int> expectedVector1{4, 3, 2, 1};
        shiv::vector<int> expectedVector2{4, 4, 4, 4, 4};
        vector1.swap(vector2);
        BOOST_TEST(vector1 == expectedVector1);
        BOOST_TEST(vector2 != expectedVector1);
        vector2.fill(4);
        BOOST_TEST(vector2 == expectedVector2);
    }
    
    BOOST_AUTO_TEST_CASE(comparison_test){
        shiv::vector<int> vector1{0, 1, 2, 3, 4};
        shiv::vector<int> vector_gt{5, 5, 5, 5, 5};
        shiv::vector<int> vector_lt{0, 0, 0, 0, 0};
        shiv::vector<int> vector2{0, 999, 0, 0, 0};
        BOOST_TEST(vector1 != vector_gt);
        BOOST_TEST(vector1 < vector_gt);
        BOOST_TEST(vector1 <= vector_gt);
        BOOST_TEST(vector1 <= shiv::vector({0, 1, 2, 3, 4}));
        BOOST_TEST(vector1 > vector_lt);
        BOOST_TEST(!(vector1 > vector2));
    }
BOOST_AUTO_TEST_SUITE_END()