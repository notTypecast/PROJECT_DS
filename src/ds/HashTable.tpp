template <typename T>
ds::HashTable<T>::HashTable(unsigned int M) : M(M), internalArray(new LinkedKey<T>[M]) {}

template <typename T>
ds::HashTable<T>::~HashTable() {
    // delete all keys in the hash table
    // LinkedKey's destructor does not delete keys, but they must be deleted here, since they are created on
    // object instantiation
    LinkedKey<T> *current;
    for (int i = 0; i < M; ++i) {
        current = &internalArray[i];
        while (current != nullptr) {
            if (current->key != nullptr) {
                delete current->key;
            }
            current = current->next;
        }
    }
    // delete array
    // this will call all destructors, therefore deleting all LinkedKey object in internalArray and
    // chain-deleting all LinkedKey objects linked to them
    delete[] internalArray;
}

template <typename T>
ds::LinkedKey<T>* ds::HashTable<T>::access(const T &key) {
    // get index of item to be accessed in array
    // since this hash table uses mod, key % M (where M is the size of internalArray) determines index of item
    int index = key % M;
    // if key at index is nullptr, item does not exist in hash table
    if (internalArray[index].key == nullptr) {
        return nullptr;
    }
    // if key at index isn't nullptr, search for key in current chain
    LinkedKey<T> *current = &internalArray[index];
    while (current != nullptr && *current->key != key) {
        current = current->next;
    }
    // return whatever was found (if not found, this will be nullptr)
    return current;
}

// TODO: explain why no edit method is used
template <typename T>
void ds::HashTable<T>::insert(const T &key) {
    // since const reference was used, first store key in heap
    T* keyInHeap = new T(key);
    // get index
    int index = key % M;
    // if internalArray is empty at that index, store this key and return
    if (internalArray[index].key == nullptr) {
        // creation of new LinkedKey object isn't necessary, since array already contains created object here
        internalArray[index].key = keyInHeap;
        return;
    }
    // else, go to end of chain and store key there
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
    // since chain is created using LinkedKey objects, new LinkedKey object needs to be created for this key
    current->next = new LinkedKey<T>(keyInHeap, nullptr);
}

template <typename T>
bool ds::HashTable<T>::remove(const T &key) {
    // get index
    int index = key % M;
    // if index has no key, cannot remove
    if (internalArray[index].key == nullptr) {
        return false;
    }
    // if key to be removed is at that index
    else if (*internalArray[index].key == key) {
        // delete the key and set LinkedKey object's key value to nullptr
        delete internalArray[index].key;
        internalArray[index].key = nullptr;
        // if there is next LinkedKey object linked to this one, its values must be moved to this one
        // this is because this LinkedKey object is part of internalArray and cannot be deleted/overwritten
        if (internalArray[index].next != nullptr) {
            // set this LinkedKey's key to be equal to the next one's key
            internalArray[index].key = internalArray[index].next->key;
            // set this LinkedKey's next to be equal to the LinkedKey object linked to the next LinkedKey object
            LinkedKey<T> *toDelete = internalArray[index].next;
            internalArray[index].next = internalArray[index].next->next;
            // delete the next LinkedKey object whose values were copied to this one safely (without chain deleting)
            ds::safeDeleteLinkedKey(toDelete);
        }
        return true;
    }

    // if first LinkedKey object does not contain the same key, we must search the chain
    // create new LinkedKey, link to beginning of chain
    LinkedKey<T> *initial = new LinkedKey<T>(nullptr, &internalArray[index]);
    LinkedKey<T> *current = initial;

    // look at next LinkedKey's key to see if it's the one to be deleted
    // this works, since, if we find the key, we can link the current LinkedKey to the next LinkedKey's next key
    // therefore skipping the next LinkedKey (whose key is the one to be removed)
    // this is also the reason a new LinkedKey is created at the beginning of the chain; the first time we look, we will
    // look at that LinkedKey object's next, which will be the first LinkedKey object
    while (*current->next->key != key) {
        current = current->next;
        // if end of chain was reached without finding
        if (current->next == nullptr) {
            // delete the initial LinkedKey object (which is the one created above)
            ds::safeDeleteLinkedKey(initial);
            return false;
        }
    }
    // key was found, so mark the next one as the one to be deleted
    LinkedKey<T> *toDelete = current->next;
    // link current one to next's next
    current->next = current->next->next;
    // delete the next one's key
    delete toDelete->key;
    // finally, safe delete (no chain-deleting) the next LinkedKey object, as well as the initial one created above
    ds::safeDeleteLinkedKey(toDelete);
    ds::safeDeleteLinkedKey(initial);
    return true;
}

template <typename T>
void ds::HashTable<T>::print() {
    // print each LinkedKey object's key that isn't null, as well as the chain it's connected to
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