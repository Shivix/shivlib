#ifndef SHIVLIB_TYPETRAITS_HPP
#define SHIVLIB_TYPETRAITS_HPP

namespace ShivLib{
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
    
    template<typename>
    struct is_lvalue_reference{
        static const bool check = false;
    };
    template<typename T>
    struct is_lvalue_reference<T&>{ // this explicitly instantiated template will be used when the argument it is an lvalue
        static const bool check = true;
    };
    
    template<typename>
    struct is_rvalue_reference{
        static const bool check = false;
    };
    template<typename T>
    struct is_rvalue_reference<T&&>{ // this explicitly instantiated template will be used when the argument it is an rvalue
        static const bool check = true;
    };
};


#endif //SHIVLIB_TYPETRAITS_HPP
