#ifndef SHIVLIB_FUNCTIONAL_HPP
#define SHIVLIB_FUNCTIONAL_HPP

#include <concepts>
#include "utility.hpp"
namespace shiv{
template <typename FuncT, typename... Args>
        requires std::invocable<FuncT, Args...>
decltype(auto) invoke(FuncT&& function, Args&&... args){
    return function(shiv::forward<Args>(args)...);
}
}

#endif//SHIVLIB_FUNCTIONAL_HPP
