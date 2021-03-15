#ifndef SHIVLIB_lUA_BIND_HPP
#define SHIVLIB_lUA_BIND_HPP

#include <concepts>
#include <lua/lua.hpp>
#include <utility>
#include <stdexcept>
#include <stack>
#include <any>
#include <vector>

namespace shiv{
    class LuaState{
    public:
        LuaState(){ // currently loads all main libs
            luaopen_base(L);
            luaopen_table(L);
            luaopen_io(L);
            luaopen_string(L);
            luaopen_math(L);
        }
    private:
        lua_State* L{luaL_newstate()};
#ifndef NDEBUG
        static constexpr bool is_debug = true;
        std::stack<std::any> stack{};
#else
        static constexpr bool is_debug = false;
#endif
        template <typename... Args>
        void get_globals(Args... args) {
            (lua_getglobal(L, args), ...);
        }

    public:
        template <typename T, typename... Args>
        void get_globals(T next, Args... args) {
            lua_getglobal(L, next);
            if constexpr (sizeof...(args) > 0) {
                get_globals(args...);
            }
        }
        
        template<typename T, typename... Args>
        requires std::integral<T> || std::floating_point<T>
        std::vector<T> num_from_lua(int amount, Args... args){
            get_globals<const char*>(args...);
            std::vector<T> result{};
            for(int i{0}; i < amount; ++i){
                result.push_back(static_cast<T>(lua_tonumber(L, -1)));
            }
        }
        
        template<typename T>
        requires std::integral<T> || std::floating_point<T>
        std::vector<T> num_from_lua(const char* variable){
            lua_getglobal(L, variable);
            return static_cast<T>(lua_tonumber(L, -1));
        }
    };
    
    
    
    
    
    /*// TODO: wrapper around another function to turn function into lua callable one
    
    template<std::invocable func, typename... Args>
    std::invoke_result_t<func, Args...> call_from_lua(lua_State* L, int luaFile, Args... args){
        // TODO: error checking

        return func(std::forward<Args>(args)...);
    }
    template<std::invocable func, typename... Args>
    std::invoke_result_t<func, Args...> call_in_lua(lua_State* L, Args... args){
        // TODO: error checking
        
        lua_pushlightuserdata(L, func(std::forward<Args>(args)...));
        return 1;
    }
    template<typename... Args>
    Args get_lua_args(Args... args){
        for(int i{0}; i < sizeof...(Args); ++i){
        }
    }   */
}


#endif//SHIVLIB_LUA_BIND_HPP
