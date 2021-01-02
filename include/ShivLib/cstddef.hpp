#ifndef SHIVLIB_CSTDDEF_HPP
#define SHIVLIB_CSTDDEF_HPP

#include <cstddef>

namespace shiv {
    using size_t = __SIZE_TYPE__;
    using ptrdiff_t = __PTRDIFF_TYPE__;
    using nullptr_t = decltype(nullptr);
}

#endif //SHIVLIB_CSTDDEF_HPP
