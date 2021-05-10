template <typename T>
ds::HashTable<T>::HashTable(unsigned int M) : M(M), internalArray(new LinkedKey<T>[M]) {}

template <typename T>
ds::HashTable<T>::~HashTable() {
    for (int i = 0; i < M; ++i) {
        // deleting each key since they are created in the insert method
        delete internalArray[i].key;
    }
    delete[] internalArray;
}

template <typename T>
ds::LinkedKey<T>* ds::HashTable<T>::access(const T &key) {
    int index = key % M;
    if (internalArray[index].key == nullptr) {
        return nullptr;
    }
    LinkedKey<T> *current = &internalArray[index];
    while (current != nullptr && *current->key != key) {
        current = current->next;
    }
    return current;
}

// TODO: explain why no edit method is used
template <typename T>
void ds::HashTable<T>::insert(const T &key) {
    T* keyInHeap = new T(key);
    int index = key % M;
    if (internalArray[index].key == nullptr) {
        internalArray[index].key = keyInHeap;
        return;
    }
    LinkedKey<T> *current = &internalArray[index];
    while (current->next != nullptr) {
        // if key exists, overwrite
        if (*current->key == key) {
            delete current->key;
            current->key = keyInHeap;
            return;
        }
        current = current->next;
    }
    current->next = new LinkedKey<T>(keyInHeap, nullptr);
}

template <typename T>
bool ds::HashTable<T>::remove(const T &key) {
    int index = key % M;
    if (internalArray[index].key == nullptr) {
        return false;
    }
    else if (*internalArray[index].key == key) {
        delete internalArray[index].key;
        internalArray[index].key = nullptr;
        if (internalArray[index].next != nullptr) {
            internalArray[index].key = internalArray[index].next->key;
            LinkedKey<T> *toDelete = internalArray[index].next;
            internalArray[index].next = internalArray[index].next->next;
            ds::safeDeleteLinkedKey(toDelete);
        }
        return true;
    }

    LinkedKey<T> *initial = new LinkedKey<T>(nullptr, &internalArray[index]);
    LinkedKey<T> *current = initial;

    while (*current->next->key != key) {
        current = current->next;
        if (current->next == nullptr) {
            ds::safeDeleteLinkedKey(initial);
            return false;
        }
    }
    LinkedKey<T> *toDelete = current->next;
    current->next = current->next->next;
    delete toDelete->key;
    ds::safeDeleteLinkedKey(toDelete);
    ds::safeDeleteLinkedKey(initial);
    return true;
}

template <typename T>
void ds::HashTable<T>::print() {
    LinkedKey<T> *current;
    for (int i = 0; i < M; ++i) {
        current = &internalArray[i];
        if (current->key == nullptr) {
            continue;
        }
        while (true) {
            std::cout << *current->key;
            if (current->next == nullptr) {
                break;
            }
            std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}