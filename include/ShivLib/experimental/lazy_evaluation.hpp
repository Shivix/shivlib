#ifndef SHIVLIB_LAZY_EVALUATION_HPP
#define SHIVLIB_LAZY_EVALUATION_HPP

#include <functional>

namespace shiv {
    template<typename T>
    class lazyEvaluation {
        std::function<T()> evaluation;
        T result{};
        bool is_evaluated{false};
        
    public:
        explicit lazyEvaluation(std::function<T()> func_ptr):
                evaluation{func_ptr}{}
        
        T get(){
            if (!is_evaluated) {
                result = evaluation();
            }
            return result;
        }
        T operator()(){
            return get();
        }
        
    };
}
#endif//SHIVLIB_LAZY_EVALUATION_HPP
