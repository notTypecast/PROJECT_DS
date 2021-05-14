#include "../../include/ds.h"
template <typename T>
ds::AVLTree<T>::AVLTree() {
    root = nullptr;
}

template <typename T>
ds::AVLTree<T>::~AVLTree() {
    // recursive lambda function
    // deleted a node's left and right children recursively, then deletes that node
    std::function<void(struct ds::AVLNode<T>*)> F = [&](struct ds::AVLNode<T> *node) {
        if (node->left != nullptr) {
            F(node->left);
        }
        if (node->right != nullptr) {
            F(node->right);
        }
        deleteNode(node);
    };
    // calling the recursive lambda on root will delete the entire tree
    F(root);
}

template <typename T>
ds::LinkedKey<T>* ds::AVLTree<T>::getMaxKey() {
    // follow right path until nullptr is reached
    // resulting node will be element with max key
    AVLNode<T> *tmp = root;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    // return a LinkedKey object containing node with max key
    return ds::createLinkedKey(tmp);
}

template <typename T>
ds::LinkedKey<T>* ds::AVLTree<T>::getMinKey() {
    // return a LinkedKey object containing node with min key
    // getSmallestNode(root) will follow left path from root
    return ds::createLinkedKey(getSmallestNode(root));
}

template <typename T>
void ds::AVLTree<T>::deleteNode(AVLNode <T> *node) {
    // delete a node and every node with the same key (linked to that node)
    AVLNode<T> *tmp;
    while (node != nullptr) {
        tmp = node->same;
        delete node;
        node = tmp;
    }
}

template <typename T>
ds::LinkedKey<T>* ds::AVLTree<T>::access(const T &key) {
    // begin at root
    AVLNode<T> *currentNode = root;

    while (currentNode != nullptr) {
        // if keys match, node found, return LinkedKey containing node
        if (currentNode->key == key) {
            return ds::createLinkedKey(currentNode);
        }
        // if current node key is smaller than key to access, go right
        else if (currentNode->key < key) {
            currentNode = currentNode->right;
        }
        // else go left
        else {
            currentNode = currentNode->left;
        }
    }

    // if key wasn't found, return nullptr
    return nullptr;
}

template <typename T>
void ds::AVLTree<T>::insert(const T &key) {
    // create new node for key to insert
    struct ds::AVLNode<T> *newNode = ds::createAVLNode(key);
    // insert at root using recursive insert method
    root = insertAtNode(root, newNode);
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::insertAtNode(AVLNode<T> *node, AVLNode<T> *newNode) {
    // if nullptr was reached, newNode must be inserted here, so return it to previous recursion level
    if (node == nullptr) {
        return newNode;
    }
    // if node with same key exists, chain them
    if (newNode->key == node->key) {
        AVLNode<T> *tmp = node;
        while (tmp->same != nullptr) {
            tmp = tmp->same;
        }
        tmp->same = newNode;
        return node;
    }

    // if key is smaller than current, go left
    if (newNode->key < node->key) {
        node->left = insertAtNode(node->left, newNode);
    }
    // else go right
    else {
        node->right = insertAtNode(node->right, newNode);
    }

    // determine height for current node
    // height is 1 + maximum height of left/right subtrees
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

    // get balance factor for current node
    // if balance factor is > 1 or < -1, rotations will be required to re-balance tree
    int balanceFactor = getNodeBalanceFactor(node);

    // balanceFactor > 1 means left subtree height is by 2 or more greater than right subtree height
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
    // balanceFactor < -1 means left subtree height is by 2 or more smaller than right subtree height
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

    // if no rotations were necessary, return current node to previous recursion level
    // so that no change to the tree is made
    return node;
}

template <typename T>
bool ds::AVLTree<T>::remove(const T &key) {
    // call recursive remove function on root
    // if key is found and removed, KEYFOUND will be adjusted by that function
    KEYFOUND = false;
    removeAtNode(root, key);
    return KEYFOUND;
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::removeAtNode(AVLNode <T> *node, const T &key) {
    // if nullptr is reached, key wasn't found, so return nullptr
    if (node == nullptr) {
        return node;
    }

    // if key is smaller than current node key, go left
    if (key < node->key) {
        node->left = removeAtNode(node->left, key);
    }
    // else if key is larger than current node key, go right
    else if (key > node->key) {
        node->right = removeAtNode(node->right, key);
    }
    // else, keys are the same, so correct node has been located
    else {
        KEYFOUND = true;
        // at most one child
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode<T> *tmp = node->left == nullptr ? node->right : node->left;
            // if the node has no children, both left and right will be null, and as a result tmp will be null.
            if (tmp == nullptr) {
                tmp = node;
                node = nullptr;
            }
            // exactly one child
            else {
                *node = *tmp;
            }
            deleteNode(tmp);
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

    // similar to insert, determine new height and balance factor
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

    int balanceFactor = getNodeBalanceFactor(node);

    // if left subtree is unbalanced
    if (balanceFactor > 1) {
        // if balance factor of left subtree >= 0, case is left left
        if (getNodeBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        // else, balance factor is < 0, so right subtree of left child is taller, therefore left right case
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // if right subtree is unbalanced
    else if (balanceFactor < -1) {
        // if balance factor of right subtree <= 0, case is right right
        if (getNodeBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        // else, balance factor is > 0, so left subtree of right child is taller, therefore right left case
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // if no rotations were necessary, return current node so no change is made to the tree
    return node;
}

template <typename T>
ds::AVLNode<T>* ds::AVLTree<T>::getSmallestNode(AVLNode <T> *subRoot) {
    // follow left path until nullptr is met to find node with smallest key
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
    // call recursive function to print tree in order
    ds::AVLNode<T> *currentNode = root;
    printInOrderRecursively(currentNode);
}

template <typename T>
void ds::AVLTree<T>::printInOrderRecursively(ds::AVLNode<T> *currentNode) {
    // if node exists
    if (currentNode != nullptr) {
        // if left child exists, call recursive print function on it
        if (currentNode->left != nullptr) {
            printInOrderRecursively(currentNode->left);
        }
        // print this node's key, as well as all nodes linked to it
        std::cout << currentNode->key;
        AVLNode<T> *tmp = currentNode->same;
        while (tmp != nullptr) {
            std::cout << " -> " << tmp->key;
            tmp = tmp->same;
        }
        std::cout << std::endl;
        // if right child exists, call recursive print function on it
        if (currentNode->right != nullptr) {
            printInOrderRecursively(currentNode->right);
        }
    }
}

template <typename T>
int ds::AVLTree<T>::getNodeHeight(ds::AVLNode<T> *node) {
    // return node height if it exists, or 0 if it doesn't
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template <typename T>
int ds::AVLTree<T>::getNodeBalanceFactor(ds::AVLNode<T> *node) {
    // get balance factor of node
    // balance factor is equal to left subtree height minus right subtree height
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