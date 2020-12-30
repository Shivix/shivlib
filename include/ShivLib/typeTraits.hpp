#ifndef SHIVLIB_TYPETRAITS_HPP
#define SHIVLIB_TYPETRAITS_HPP

#include "cstddef.hpp"

namespace ShivLib{
    // remove refness of a type
    template<typename T>
    struct remove_reference{
        using type = T;
    };
    template<typename T>
    struct remove_reference<T&>{
        using type = T;
    };
    template<typename T>
    struct remove_reference<T&&>{
        using type = T;
    };
    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type; // add partially specialised aliases pls
    
    // remove pointer from a type
    template<typename T>
    struct remove_pointer{
        using type = T;
    };
    template<typename T>
    struct remove_pointer<T*>{
        using type = T;
    };
    template<typename T>
    using remove_pointer_t = typename remove_pointer<T>::type;

    // remove both pointer and reference
    template<typename T>
    struct remove_pr{
        using type = remove_pointer_t<remove_reference_t<T>>;
    };
    template<typename T> // could be alias from start but kept like this for consistency
    using remove_pr_t = typename remove_pr<T>::type;
    
    // remove qualifier of a type
    template<typename T>
    struct remove_const{
        using type = T; // returns the type as it is
    };
    template<typename T>
    struct remove_const<const T>{ // only used if value is already const
        using type = T; // will return the non const type
    };
    template<typename T>
    using remove_const_t = typename remove_const<T>::type;
    
    // remove volatile qualifier type
    template<typename T>
    struct remove_volatile{
        using type = T;
    };
    template<typename T>
    struct remove_volatile<volatile T>{
        using type = T;
    };
    template<typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;
    
    // remove both volatile and const qualifiers
    template<typename T>
    struct remove_cv{
        using type = typename remove_const<typename remove_volatile<T>::type>::type;
    };
    template<typename T> // could be alias from start but kept like this for consistency
    using remove_cv_t = typename remove_cv<T>::type;
    
    
    // integral constants -- A C++17 only variant of integral constant using auto template parameter
    template<auto v>
    struct integral_constant{
        using value_type = decltype(v);
        using type = integral_constant<v>;
        
        static constexpr value_type value = v;
        
        constexpr operator value_type() const noexcept{ // NOLINT implicit casts allowed
            return value;
        }
        constexpr value_type operator() () const noexcept{ // allows struct to be used as functor
            return value;
        }
    };

    using true_type = integral_constant<true>;
    using false_type = integral_constant<false>;
    
    // conditionals
    template<bool, typename isTrue, typename isFalse>
    struct conditional{
        using type = isTrue;
    };
    template<typename isTrue, typename isFalse>
    struct conditional<false, isTrue, isFalse>{
        using type = isFalse;
    };
    
    template<bool condition, typename isTrue, typename isFalse>
    using conditional_t = typename conditional<condition, isTrue, isFalse>::type;
    
    // enable_if
    template<bool, typename T = void>
    struct enable_if{};
    template<typename T>
    struct enable_if<true, T>{
        using type = T;
    };
    template<bool condition, typename T>
    using enable_if_t = typename enable_if<condition, T>::type;

    // is_same
    template<typename T1, typename T2>
    struct is_same: false_type {};
    template<typename T>
    struct is_same<T, T>: true_type {};
    template<typename T1, typename T2>
    inline constexpr bool is_same_v = is_same<T1, T2>::value;
    
    // check reference type
    template<typename>
    struct is_lvalue_reference: public false_type{};
    template<typename T>
    struct is_lvalue_reference<T&>: public true_type{}; // this partially specialised template will be used when the argument it is an lvalue
    template<typename T>
    inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
    
    template<typename>
    struct is_rvalue_reference: public false_type{};
    template<typename T>
    struct is_rvalue_reference<T&&>: public true_type{}; // this partially specialised template will be used when the argument it is an rvalue
    template<typename T>
    inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
    
    template<typename T>
    struct is_reference: public integral_constant<is_lvalue_reference_v<T> || is_rvalue_reference_v<T>> {};
    template<typename T>
    inline constexpr bool is_reference_v = is_reference<T>::value;
    
    // pointer check
    template<typename T>
    struct is_pointer_helper: false_type {};
    template<typename T>
    struct is_pointer_helper<T*>: true_type {};

    template<typename T>
    struct is_pointer: is_pointer_helper<remove_cv_t<T>> {};
    
    // integral check
    template<typename>
    struct is_integral_helper: public false_type {};
    template<>
    struct is_integral_helper<bool>: public true_type {};
    template<>
    struct is_integral_helper<char>: public true_type {};
    template<>
    struct is_integral_helper<signed char>: public true_type {};
    template<>
    struct is_integral_helper<unsigned char>: public true_type {};
    template<>
    struct is_integral_helper<wchar_t>: public true_type {};
    template<>
    struct is_integral_helper<char16_t>: public true_type {};
    template<>
    struct is_integral_helper<char32_t>: public true_type {};
    template<>
    struct is_integral_helper<short>: public true_type {};
    template<>
    struct is_integral_helper<unsigned short>: public true_type {};
    template<>
    struct is_integral_helper<int>: public true_type {};
    template<>
    struct is_integral_helper<unsigned int>: public true_type {};
    template<>
    struct is_integral_helper<long>: public true_type {};
    template<>
    struct is_integral_helper<unsigned long>: public true_type {};
    template<>
    struct is_integral_helper<long long>: public true_type {};
    template<>
    struct is_integral_helper<unsigned long long>: public true_type {};

    template<typename T>
    struct is_integral: public is_integral_helper<remove_cv_t<T>>{};
    
    template<typename T>
    inline constexpr bool is_integral_v = is_integral<T>::value;
    
    // floating point check
    template<typename>
    struct is_floating_point_helper: public false_type {};
    template<>
    struct is_floating_point_helper<float>: public true_type {};
    template<>
    struct is_floating_point_helper<double>: public true_type {};
    template<>
    struct is_floating_point_helper<long double>: public true_type {};

    template<typename T>
    struct is_floating_point: public is_floating_point_helper<remove_cv_t<T>> {};
    
    template<typename T>
    inline constexpr bool is_floating_point_v = is_floating_point<T>::value;
    
    // arithmetic type check
    template<typename T>
    struct is_arithmetic : public integral_constant<is_integral_v<T> || is_floating_point_v<T>> {};

    template<typename T>
    inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
    
    // void check -- const/ volatile qualifiers do not change outcome
    template<typename>
    struct is_void_helper: public false_type {};
    template<>
    struct is_void_helper<void>: public true_type {};
    
    template<typename T>
    struct is_void: public is_void_helper<remove_cv_t<T>>::type {};

    template<typename T>
    using is_void_t = typename is_void<T>::type;

    // is_array
    template<typename>
    struct is_array: public false_type {};
    template<typename T, size_t size>
    struct is_array<T[size]>: public true_type {};
    template<typename T>
    struct is_array<T[]>: public true_type {};
    
    // const check
    template<typename>
    struct is_const: public false_type{};

    template<typename T>
    struct is_const<const T>: public true_type{};

    // volatile check
    template<typename>
    struct is_volatile: public false_type{};

    template<typename T>
    struct is_volatile<volatile T>: public true_type{};
}


#endif //SHIVLIB_TYPETRAITS_HPP
