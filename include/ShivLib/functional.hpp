#ifndef SHIVLIB_FUNCTIONAL_HPP
#define SHIVLIB_FUNCTIONAL_HPP

#include <concepts>
#include "utility.hpp"
#include "type_traits.hpp"
#include <tuple>

namespace shiv{
template <typename FuncT, typename... Args>
        requires std::invocable<FuncT, Args...>
constexpr decltype(auto) invoke(FuncT&& function, Args&&... args){
    return function(shiv::forward<Args>(args)...);
}


// TODO: to be moved to own tuple implmentation
template <typename FuncT, typename TupleT, size_t... seq>
constexpr decltype(auto) apply_impl(FuncT&& function, TupleT&& tuple, std::index_sequence<seq...>){
    return shiv::invoke(shiv::forward<FuncT>(function), std::get<seq>(shiv::forward<TupleT>(tuple))...);
}
template <typename FuncT, typename TupleT>
constexpr decltype(auto) apply(FuncT&& function, TupleT&& tuple){
    return apply_impl(shiv::forward<FuncT>(function), shiv::forward<TupleT>(tuple), std::make_index_sequence<std::tuple_size_v<shiv::remove_reference_t<TupleT>>>{});
}

template<typename... Args>
constexpr auto forward_as_tuple(Args&&... args){
    return std::tuple<Args&&...>{std::forward<Args>(args)...};
}
} // namespace shiv
#endif//SHIVLIB_FUNCTIONAL_HPP
