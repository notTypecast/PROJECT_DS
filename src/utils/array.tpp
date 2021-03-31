template <typename T>
bool utils::array::compare(const T arr1[], std::size_t arr1Size, const T arr2[], std::size_t arr2Size) {
    //arrays must be equal size
    if (arr1Size != arr2Size) {
        return false;
    }

    //loop through elements
    for (arr1Size = 0; arr1Size < arr2Size; ++arr1Size) {
        //if element in same index is different, arrays aren't equal
        if (arr1[arr1Size] != arr2[arr1Size]) {
            return false;
        }
    }

    return true;
}

template <typename T>
T* utils::array::duplicate(T arr[], std::size_t arrSize) {
    T newArr[] = new T[arrSize];

    for (int i = 0; i < arrSize; ++i) {
        newArr[i] = arr[i];
    }

    return newArr;
}
