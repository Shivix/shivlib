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
    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;
    
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
    template<bool condition, typename isTrue, typename isFalse>
    struct conditional{
        using type = isTrue;
    };
    template<typename isTrue, typename isFalse>
    struct conditional<false, isTrue, isFalse>{
        using type = isFalse;
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
    template<typename... args>
    using or_conditional_v = typename or_conditional<args...>::value;
    
    template<typename...>
    struct and_conditional;
    template<>
    struct and_conditional<>: public true_type{};
    template<typename T1>
    struct and_conditional<T1>: public T1{};
    template<typename T1, typename T2>
    struct and_conditional<T1, T2>: public conditional<T1::value, T1, T2>::type {};
    template<typename... args>
    using and_conditional_v = typename and_conditional<args...>::value;
    
    // check reference type
    template<typename>
    struct is_lvalue_reference: public false_type{};
    template<typename T>
    struct is_lvalue_reference<T&>: public true_type{}; // this partially specialised template will be used when the argument it is an lvalue
    template<typename T>
    using is_lvalue_reference_v = typename is_lvalue_reference<T>::value;
    
    template<typename>
    struct is_rvalue_reference: public false_type{};
    template<typename T>
    struct is_rvalue_reference<T&&>: public true_type{}; // this partially specialised template will be used when the argument it is an rvalue
    template<typename T>
    using is_rvalue_reference_v = typename is_rvalue_reference<T>::value;
    
    template<typename T>
    struct is_reference: public or_conditional<is_lvalue_reference<T>, is_rvalue_reference<T>>::type {};
    template<typename T>
    using is_reference_v = typename is_reference<T>::value;
    
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
    struct is_integral: public is_integral_helper<remove_cv_t<T>>::type {};
    
    template<typename T>
    using is_integral_v = typename is_integral<T>::value;
    
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
    struct is_floating_point: public is_floating_point_helper<remove_cv_t<T>>::type {};
    
    template<typename T>
    using is_floating_point_v = typename is_floating_point<T>::value;
    
    // void check -- const/ volatile qualifiers do not change outcome
    template<typename>
    struct is_void_helper: public false_type {};
    template<>
    struct is_void_helper<void>: public true_type {};
    template<typename T>
    struct is_void: public is_void_helper<remove_cv_t<T>>::type {};
}


#endif //SHIVLIB_TYPETRAITS_HPP
