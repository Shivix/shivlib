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
    
    // check reference type
    template<typename>
    struct is_lvalue_reference: public false_type{};
    template<typename T>
    struct is_lvalue_reference<T&>: public true_type{}; // this explicitly instantiated template will be used when the argument it is an lvalue
    template<typename>
    struct is_rvalue_reference: public false_type{};
    template<typename T>
    struct is_rvalue_reference<T&&>: public true_type{}; // this explicitly instantiated template will be used when the argument it is an rvalue
}


#endif //SHIVLIB_TYPETRAITS_HPP
