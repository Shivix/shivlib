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
        bool check = false;
    };
    template<typename T>
    struct is_lvalue_reference<T&>{ // this overloaded struct will be used if it is an lvalue
        bool check = true;
    };
    
    template<typename>
    struct is_rvalue_reference{
        bool check = false;
    };
    template<typename T>
    struct is_rvalue_reference<T&&>{ // this overloaded struct will be used if it is an rvalue
        bool check = true;
    };
};


#endif //SHIVLIB_TYPETRAITS_HPP
