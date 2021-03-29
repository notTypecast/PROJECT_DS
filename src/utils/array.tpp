template <typename T>
bool compare(T arr1[], size_t arr1Size, T arr2[], size_t arr2Size) {
    //arrays must be equal size
    if (arr1Size != arr2Size) {
        return false;
    }

    for (arr1Size = 0; arr1Size < arr2Size; ++arr1Size) {
        if (arr1[arr1Size] != arr2[arr2Size]) {
            return false;
        }
    }

    return true;
}
