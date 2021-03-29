#ifndef UTILS_H
#define UTILS_H

namespace utils {
    namespace array {
        template <typename T>
        bool compare(T arr1[], size_t arr1Size, T arr2[], size_t arr2Size);
    }
}

#include "../src/utils/array.tpp"

#endif
