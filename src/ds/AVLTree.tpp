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
void ds::AVLTree<T>::insert(T key) {
    struct ds::AVLNode<T> *newNode = ds::createAVLNode(key);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    root = insertAtNode(root, newNode);

    //need to rotate
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::insertAtNode(AVLNode<T> *node, AVLNode<T> *newNode) {
    if (newNode->key == node->key) {
        delete newNode;
        return node;
    }
    if (node == nullptr) {
        return newNode;
    }

    if (newNode->key < node->key) {
        node->left = insertAtNode(node->left, newNode);
    }
    else {
        std::cout << "and here" << std::endl;
        node->right = insertAtNode(node->right, newNode);
    }

    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

    int balanceFactor = getNodeBalanceFactor(node);

    if (balanceFactor > 1) {
        //Left left case
        if (newNode->key < node->left->key) {
            std::cout << "left left case" << std::endl;
            rightRotate(node);
        }
        //Left right case
        else {
            std::cout << "left right case" << std::endl;
            leftRotate(node->left);
            rightRotate(node);
        }
    }
    else if (balanceFactor < -1) {
        //Right left case
        if (newNode->key < node->right->key) {
            std::cout << "right left case" << std::endl;
            rightRotate(node->right);
            leftRotate(node);
        }
        //Right right case
        else {
            leftRotate(node);
        }
    }

    return node;

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