template <typename T>
struct ds::AVLNode<T>* ds::createAVLNode(const T &key) {
    // create new AVL node with given key and height 1
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
    // create first LinkedKey object
    LinkedKey<T> *current = new LinkedKey<T>(&node->key, nullptr);
    LinkedKey<T> *toReturn = current;
    // for each node linked to this node, create new LinkedKey object and link it to previous LinkedKey object
    while (node->same != nullptr) {
        current->next = new LinkedKey<T>(&node->same->key, nullptr);
        node = node->same;
        current = current->next;
    }
    // return first LinkedKey object
    return toReturn;
}

template <typename T>
ds::LinkedKey<T>::LinkedKey() : key(nullptr), next(nullptr) {}

template <typename T>
ds::LinkedKey<T>::LinkedKey(T *key, ds::LinkedKey<T> *next) : key(key), next(next) {}

template <typename T>
ds::LinkedKey<T>::~LinkedKey() {
    // chain delete by calling next element destructor
    // this destructor does not delete the key stored in the LinkedKey object, only the object
    // and all the LinkedKey object linked to it
    if (next != nullptr) {
        delete next;
    }
}

template <typename T>
void ds::safeDeleteLinkedKey(LinkedKey<T> *key) {
    if (key == nullptr) {
        return;
    }
    // unlink this LinkedKey from the next LinkedKey, then delete it
    // this is done to prevent chain deletion wherever required
    key->next = nullptr;
    delete key;
}