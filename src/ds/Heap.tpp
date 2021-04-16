template <typename T>
ds::Heap<T>::Heap(std::size_t maxSize) : createdArray(true), internalArray(new T[maxSize]), currentSize(0), maxSize(maxSize) {
};

template <typename T>
ds::Heap<T>::Heap(T** array, std::size_t size, std::size_t maxSize) : createdArray(false), internalArray(new T[maxSize]), currentSize(0), maxSize(maxSize) {
    if (maxSize < size) {
        throw std::invalid_argument("maxSize cannot be smaller than size.");
    }

    for (int i = 0; i < size; ++i) {
        insert((*array)[i]);
    }

    delete[] *array;
    *array = internalArray;
};

template <typename T>
ds::Heap<T>::~Heap() {
    if (createdArray) {
        delete[] internalArray;
    }
}

template <typename T>
int ds::Heap<T>::getParent(int index) {
    return (index - 1) / 2;
}

template <typename T>
int ds::Heap<T>::getRightChild(int index) {
    return 2*index + 2;
}

template <typename T>
int ds::Heap<T>::getLeftChild(int index) {
    return 2*index + 1;
}


template <typename T>
void ds::Heap<T>::heapifyUp(int index) {
    int parentIndex = getParent(index);
    if (internalArray[index] > internalArray[parentIndex]) {
        utils::swap<int>(internalArray[index], internalArray[parentIndex]);
        heapifyUp(parentIndex);
    }
}

template <typename T>
void ds::Heap<T>::heapifyDown(int index) {
    int leftChildIndex = getLeftChild(index);
    int rightChildIndex = getRightChild(index);

    if (internalArray[index] >= internalArray[leftChildIndex] && internalArray[index] >= internalArray[rightChildIndex]) {
        return;
    }

    int indexOfMax = internalArray[leftChildIndex] > internalArray[rightChildIndex] ? leftChildIndex : rightChildIndex;
    utils::swap(internalArray[index], internalArray[indexOfMax]);

    heapifyDown(indexOfMax);
}

template <typename T>
void ds::Heap<T>::insert(T item) {
    if (currentSize == maxSize) {
        throw std::out_of_range("Heap max size reached.");
    }

    internalArray[currentSize] = item;
    heapifyUp(currentSize++);
}

template <typename T>
T ds::Heap<T>::extract(int index) {
    if (!currentSize) {
        throw std::out_of_range("Heap is empty.");
    }

    T extractedItem = internalArray[index];
    internalArray[index] = internalArray[--currentSize];
    heapifyDown(index);

    return extractedItem;
}

template <typename T>
void ds::Heap<T>::print() {
    for (int i = 0; i < currentSize; ++i) {
        std::cout << internalArray[i] << " ";
    }
}