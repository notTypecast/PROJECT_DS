template <typename T>
struct ds::AVLNode<T>* ds::createAVLNode(const T &key) {
    struct ds::AVLNode<T> *newNode = new struct ds::AVLNode<T>();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->same = nullptr;
    newNode->height = 1;
    return newNode;
}

template <typename T>
ds::LinkedKey<T>* ds::createLinkedKey(AVLNode <T> *node) {
    if (node == nullptr) {
        return nullptr;
    }
    LinkedKey<T> *current = new LinkedKey<T>(&node->key, nullptr);
    LinkedKey<T> *toReturn = current;
    while (node->same != nullptr) {
        current->next = new LinkedKey<T>(&node->same->key, nullptr);
        node = node->same;
        current = current->next;
    }
    return toReturn;
}

template <typename T>
ds::LinkedKey<T>::LinkedKey() : key(nullptr), next(nullptr) {}

template <typename T>
ds::LinkedKey<T>::LinkedKey(T *key, ds::LinkedKey<T> *next) : key(key), next(next) {}

template <typename T>
ds::LinkedKey<T>::~LinkedKey() {
    // chain delete by calling next element destructor
    if (next != nullptr) {
        delete next;
    }
}

template <typename T>
void ds::safeDeleteLinkedKey(LinkedKey<T> *key) {
    if (key == nullptr) {
        return;
    }
    key->next = nullptr;
    delete key;
}