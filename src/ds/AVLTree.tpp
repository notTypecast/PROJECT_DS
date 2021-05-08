template <typename T>
struct ds::AVLNode<T>* ds::createAVLNode(T key) {
    struct ds::AVLNode<T> *newNode = new struct ds::AVLNode<T>();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}


template <typename T>
ds::AVLTree<T>::AVLTree() {
    root = nullptr;
}

template <typename T>
ds::AVLTree<T>::~AVLTree() {
    std::function<void(struct ds::AVLNode<T>*)> F = [&](struct ds::AVLNode<T> *node) {
        if (node->left != nullptr) {
            F(node->left);
        }
        if (node->right != nullptr) {
            F(node->right);
        }
        delete node;
    };

    F(root);
}

template <typename T>
T* ds::AVLTree<T>::access(T key) {
    AVLNode<T> *currentNode = root;

    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return &currentNode->key;
        }
        else if (currentNode->key < key) {
            currentNode = currentNode->right;
        }
        else {
            currentNode = currentNode->left;
        }
    }

    return nullptr;
}

template <typename T>
void ds::AVLTree<T>::insert(T key) {
    struct ds::AVLNode<T> *newNode = ds::createAVLNode(key);
    root = insertAtNode(root, newNode);
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::insertAtNode(AVLNode<T> *node, AVLNode<T> *newNode) {
    if (node == nullptr) {
        return newNode;
    }
    if (newNode->key == node->key) {
        delete newNode;
        return node;
    }

    if (newNode->key < node->key) {
        node->left = insertAtNode(node->left, newNode);
    }
    else {
        node->right = insertAtNode(node->right, newNode);
    }

    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

    int balanceFactor = getNodeBalanceFactor(node);

    if (balanceFactor > 1) {
        //Left left case
        if (newNode->key < node->left->key) {
            return rightRotate(node);
        }
        //Left right case
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (balanceFactor < -1) {
        //Right left case
        if (newNode->key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        //Right right case
        else {
            return leftRotate(node);
        }
    }

    return node;
}

template <typename T>
bool ds::AVLTree<T>::remove(T key) {
    KEYFOUND = false;
    removeAtNode(root, key);
    return KEYFOUND;
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::removeAtNode(AVLNode <T> *node, T key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = removeAtNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = removeAtNode(node->right, key);
    }
    else {
        KEYFOUND = true;
        // at most one child
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode<T> *tmp = node->left == nullptr ? node->right : node->left;
            // If the node has no children, both left and right will be null, and as a result tmp will be null.
            if (tmp == nullptr) {
                tmp = node;
                node = nullptr;
            }
            // exactly one child
            else {
                *node = *tmp;
            }
            delete tmp;
        }
        // two children
        else {
            AVLNode<T> *tmp = getSmallestNode(node->right);
            // replacing key with min value of right subtree to preserve BST property
            node->key = tmp->key;
            // removing node that the deleted node was replaced with from its original position
            node->right = removeAtNode(node->right, tmp->key);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

    int balanceFactor = getNodeBalanceFactor(node);

    if (balanceFactor > 1) {
        // Left left case
        if (getNodeBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        // Left right case
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (balanceFactor < -1) {
        // Right right case
        if (getNodeBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        // Right left case
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::getSmallestNode(AVLNode <T> *subRoot) {
    if (subRoot == nullptr) {
        return nullptr;
    }
    while (subRoot->left != nullptr) {
        subRoot = subRoot->left;
    }
    return subRoot;
}


template <typename T>
void ds::AVLTree<T>::printInOrder() {
    ds::AVLNode<T> *currentNode = root;
    printInOrderRecursively(currentNode);
}

template <typename T>
void ds::AVLTree<T>::printInOrderRecursively(ds::AVLNode<T> *currentNode) {
    if (currentNode != nullptr) {
        if (currentNode->left != nullptr) {
            printInOrderRecursively(currentNode->left);
        }
        std::cout << currentNode->key << std::endl;
        if (currentNode->right != nullptr) {
            printInOrderRecursively(currentNode->right);
        }
    }
}

template <typename T>
int ds::AVLTree<T>::getNodeHeight(ds::AVLNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template <typename T>
int ds::AVLTree<T>::getNodeBalanceFactor(ds::AVLNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::rightRotate(AVLNode <T> *node) {
    ds::AVLNode<T> *x = node->left;
    ds::AVLNode<T> *T2 = x->right;

    x->right= node;
    node->left = T2;

    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    x->height = 1 + std::max(getNodeHeight(x->left), getNodeHeight(x->right));

    return x;
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::leftRotate(AVLNode <T> *node) {
    ds::AVLNode<T> *y = node->right;
    ds::AVLNode<T> *T2 = y->left;

    y->left = node;
    node->right = T2;

    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    y->height = 1 + std::max(getNodeHeight(y->left), getNodeHeight(y->right));

    return y;
}