#include <chrono>
#include <iostream>
#include <vector>

#include <jemalloc/jemalloc.h>

#include <ShivLib/utility.hpp>

extern "C" {
int mallctl(const char*, void*, size_t*, void*, size_t) __attribute__((weak));
}
bool is_jemalloc_linked() {
    return mallctl != nullptr;
}

[[nodiscard]] void* operator new(std::size_t size) {
    return malloc(size);
}
void operator delete(void* ptr) noexcept {
    return free(ptr);
}
void operator delete(void* ptr, std::size_t) noexcept {
    return free(ptr);
}

int main() {
    auto start{std::chrono::steady_clock::now()};
    for (auto i{0}; i < 10000; ++i) {
        std::vector<int> test(50000);
        std::vector<std::string> test2(5000);
        shiv::do_not_optimise(&test);
        shiv::do_not_optimise(&test2);
    }
    auto end{std::chrono::steady_clock::now()};
    malloc_stats_print(nullptr, nullptr, nullptr);
    std::cout << "is jemalloc linked: " << is_jemalloc_linked() << std::endl;
    auto duration{std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)};
    std::cout << duration << std::endl;
    return 0;
}
