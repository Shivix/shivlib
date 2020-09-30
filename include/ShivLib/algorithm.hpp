#ifndef SHIVLIB_ALGORITHM_HPP
#define SHIVLIB_ALGORITHM_HPP


namespace ShivLib{

    template<typename T>
    constexpr inline const T& // TODO: add concept in C++20
    max(const T& a, const T& b){
        if(a > b){
            return a;
        }
        else{
            return b;
        }
    }
    template<typename T, typename callable>
    constexpr inline const T&
    max(const T& a, const T& b, callable comparisonFunc){
        if(comparisonFunc(a > b)){
            return a;
        }
        else{
            return b;
        }
    }

    template<typename T>
    constexpr inline const T&
    min(const T& a, const T& b){
        if(a < b){
            return a;
        }
        else{
            return b;
        }
    }
    template<typename T, typename callable>
    constexpr inline const T&
    min(const T& a, const T& b, callable comparisonFunc){
        if(comparisonFunc(a < b)){
            return a;
        }
        else{
            return b;
        }
    }
    
    
    
}


#endif //SHIVLIB_ALGORITHM_HPP
