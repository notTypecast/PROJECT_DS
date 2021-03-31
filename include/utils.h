#ifndef UTILS_H
#define UTILS_H

namespace utils {

    template <typename T>
    void swap(T &item1, T &item2);

    namespace array {
        template <typename T>
        bool compare(const T arr1[], std::size_t arr1Size, const T arr2[], std::size_t arr2Size);

        template <typename T>
        T[] duplicate(T[] arr, std::size_t arrSize);
    }
}

#include "../src/utils/array.tpp"
#include "../src/utils/utils.tpp"

#endif
