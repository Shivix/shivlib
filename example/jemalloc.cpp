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

template <typename T>
struct JeAlloc {
    using value_type = T;

    [[nodiscard]] T* allocate(size_t n) {
        return reinterpret_cast<T*>(operator new(n));
    }
    void deallocate(void* ptr) {
        operator delete(ptr);
    }
    void deallocate(void* ptr, size_t) {
        operator delete(ptr);
    }
};

int main() {
    std::vector<int, JeAlloc<int>> test(50000);
    shiv::do_not_optimise(&test);
    malloc_stats_print(nullptr, nullptr, nullptr);
    std::cout << is_jemalloc_linked();
    return 0;
}
