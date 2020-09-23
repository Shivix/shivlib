#ifndef SHIVLIB_TYPETRAITS_HPP
#define SHIVLIB_TYPETRAITS_HPP

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
    
    // remove qualifier of a type
    template<typename T>
    struct remove_const{
        using type = T; // returns the type as it is
    };
    template<typename T>
    struct remove_const<const T>{ // only used if value is already const
        using type = T; // will return the non const type
    };
    
    // remove volatile qualifier type
    template<typename T>
    struct remove_volatile{
        using type = T;
    };
    template<typename T>
    struct remove_volatile<volatile T>{
        using type = T;
    };
    
    // remove both volatile and const qualifiers
    template<typename T>
    struct remove_cv{
        using type = typename remove_const<typename remove_volatile<T>::type>::type;
    };
    
    // integral constants
    template<typename T, T v>
    struct integral_constant{
        using value_type = T;
        using type = integral_constant<T, v>;
        
        static constexpr T value = v;
        
        constexpr operator value_type() const noexcept{ // NOLINT implicit casts allowed
            return value;
        }
        constexpr value_type operator() () const noexcept{ // allows struct to be used as functor
            return value;
        }
    };
    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;
    
    // conditionals
    template<bool condition, typename ifTrue, typename ifFalse>
    struct conditional{
        using type = ifTrue;
    };
    template<typename ifTrue, typename ifFalse>
    struct conditional<false, ifTrue, ifFalse>{
        using type = ifFalse;
    };
    
    template<bool, typename T = void>
    struct enable_if{};
    template<typename T>
    struct enable_if<true, T>{
        using type = T;
    };
    
    template<typename...>
    struct or_conditional;
    template<>
    struct or_conditional<>: public false_type{};
    template<typename T1>
    struct or_conditional<T1>: public T1{};
    template<typename T1, typename T2>
    struct or_conditional<T1, T2>: public conditional<T1::value, T1, T2>::type {};

    template<typename...>
    struct and_conditional;
    template<>
    struct and_conditional<>: public true_type{};
    template<typename T1>
    struct and_conditional<T1>: public T1{};
    template<typename T1, typename T2>
    struct and_conditional<T1, T2>: public conditional<T1::value, T1, T2>::type {};
    
    // check reference type
    template<typename>
    struct is_lvalue_reference: public false_type{};
    template<typename T>
    struct is_lvalue_reference<T&>: public true_type{}; // this specialised template will be used when the argument it is an lvalue
    template<typename>
    struct is_rvalue_reference: public false_type{};
    template<typename T>
    struct is_rvalue_reference<T&&>: public true_type{}; // this specialised template will be used when the argument it is an rvalue
    template<typename T>
    struct is_reference: public or_conditional<is_lvalue_reference<T>, is_rvalue_reference<T>>::type {};
    
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
    struct is_integral: public is_integral_helper<typename remove_cv<T>::type>::type {};

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
    struct is_floating_point: public is_floating_point_helper<typename remove_cv<T>::type>::type {};
    
    // variable templates C++17 needed
#if __cplusplus >= 201703L
    template<typename T>
    inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
    template<typename T>
    inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
    template<typename T>
    inline constexpr bool is_reference_v = is_reference<T>::value;
#endif
}


#endif //SHIVLIB_TYPETRAITS_HPP
