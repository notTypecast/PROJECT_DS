#ifndef DS_H
#define DS_H

#include "utils.h"

/// \brief This namespace will hold all the data structures needed in the project.
namespace ds {

    /// \brief Specialized implementation of a max heap to handle StockDayData.
    class StockHeap {
    public:
        StockHeap(std::size_t maxSize);

        /// \brief Initialized the heap using an existing StockDayData array.
        /// \param array StockDayData array used to initialized the heap. Passing double pointer since we need
        /// to reassign the array to the new internal array created.
        /// \param size Size of the array passed as an argument.
        /// \param maxSize Defines max size of internal array and, as a result, the max size of the heap.
        StockHeap(utils::stock::StockDayData **array, std::size_t size, std::size_t maxSize);

        ~StockHeap();

        /// \brief Inserts StockDayData object to the heap.
        void insert(utils::stock::StockDayData &item);

        /// \brief Extracts item at given index from the heap.
        /// \details Performs necessary rearrangements to preserve max heap structure.
        utils::stock::StockDayData extract(int index);

        /// \brief Returns current size of the heap.
        int getCurrentSize() const;

        void print() const;

    private:
        utils::stock::StockDayData *internalArray;
        const std::size_t maxSize;
        int currentSize;
        bool createdArray;

        // Helper methods to get indices of nodes relative to given index.
        static int getParent(int index);

        static int getRightChild(int index);

        static int getLeftChild(int index);

        // Methods used to preserve the heap structure.
        void heapifyUp(int index);

        void heapifyDown(int index);
    };

    /// \brief Serves as a node of the AVL tree.
    /// \details Height is measured from the bottom.
    template<typename T>
    struct AVLNode {
        T key;
        AVLNode *left;
        AVLNode *right;
        AVLNode *same;
        int height;
    };

    //TODO: mention that LinkedKey's destructor is responsible for deleting next, but not key
    template<typename T>
    struct LinkedKey {
        LinkedKey();

        LinkedKey(T *key, LinkedKey<T> *next);

        /// \details Causes chain deletion of linked notes. Does not delete inner key pointer.
        ~LinkedKey();

        T *key;
        LinkedKey *next;
    };

    /// \brief Creates an AVL node given a key of type T.
    /// \details Initializes fields appropriately.
    template<typename T>
    struct AVLNode<T> *createAVLNode(const T &key);

    /// \brief Creates a LinkedKey given an AVLNode.
    /// \details If the AVLNode points to "same" nodes, this function creates LinkedKeys for these as well.
    template<typename T>
    LinkedKey<T> *createLinkedKey(AVLNode<T> *node);

    template<typename T>
    /// \brief Deletes linked key without deleting chain
    /// \details Safely detaches and deletes LinkedKey. Does not delete internal key pointer.
    void safeDeleteLinkedKey(LinkedKey<T> *key);

    template<typename T>
    class AVLTree {
    public:
        AVLTree();

        ~AVLTree();

        /// \details This method returns a pointer to the key of the element being accessed.
        /// The actual key of the element should never be edited (since this can destroy the balance of the AVL tree).
        /// Only edit the element using the pointer if the tree type is non-primitive and the properties being
        /// edited are not the key.
        ds::LinkedKey<T> *access(const T &key);

        /// \brief Inserts key in tree.
        /// \details Uses private method to recursively insert and balance the tree after insertion.
        void insert(const T &key);

        /// \brief Removes key from tree.
        /// \returns True if key was found and successfully removed.
        /// \details Uses private method to recursively remove and balance the tree after insertion
        bool remove(const T &key);

        /// \brief Finds node with minimum key.
        /// \details Returns LinkedKey of the key found.
        ds::LinkedKey<T> *getMinKey();

        /// \brief Finds node with maximum key.
        /// \details Returns LinkedKey of the key found.
        ds::LinkedKey<T> *getMaxKey();

        /// \brief Prints tree using in-order traversal.
        /// \details Entries with same values are denoted using "->".
        void printInOrder();

    private:
        struct AVLNode<T> *root;
        // Variable used to indicate if requested key was found.
        // Used when removing a key with the remove method.
        bool KEYFOUND;

        /// \brief Internal method to recursively print in-order.
        /// \details This method is wrapped by printInOrder public method.
        void printInOrderRecursively(ds::AVLNode<T> *currentNode);

        /// \brief Returns height of the given node
        int getNodeHeight(ds::AVLNode<T> *node);

        /// \brief Returns balance factor of given node using the (leftSubTreeHeight - rightSubTreeHeight) formula.
        int getNodeBalanceFactor(ds::AVLNode<T> *node);

        /// \brief Internal method called recursively by insert public method.
        /// \details Performs balancing of the tree after successful insertion. If value of the given key
        /// already exists in the tree, the new node does not become part of the tree, but is attached to the node
        /// with the same value via the "same" pointer.
        AVLNode<T> *insertAtNode(AVLNode<T> *node, AVLNode<T> *newNode);

        /// \brief Internal method called recursively by insert remove method.
        /// \details Performs balancing of the tree after successful removal.
        AVLNode<T> *removeAtNode(AVLNode<T> *node, const T &key);

        /// \brief Helper method to rotate right using given node as pivot.
        /// \returns Node located where pivot was before the call.
        AVLNode<T> *rightRotate(AVLNode<T> *node);

        /// \brief Helper method to rotate left using given node as pivot.
        /// \returns Node located where pivot was before the call.
        AVLNode<T> *leftRotate(AVLNode<T> *node);

        /// \brief Internal method called recursively by getMinKey public method.
        /// \param subRoot Root of subtree to traverse and find node with smallest value.
        AVLNode<T> *getSmallestNode(AVLNode<T> *subRoot);

        /// \brief Deletes AVLNode.
        /// \Details Deletes AVLNode and subsequent nodes connected to it because of same key.
        void deleteNode(AVLNode<T> *node);
    };

    /// \brief Hash Table with chaining using modulo based hashing.
    template<typename T>
    class HashTable {
    public:
        /// \brief Initialized hash table.
        /// \param M Size of internal array. Will be used as a divisor when modulo of element is needed.
        HashTable(unsigned int M);

        /// \brief Deletes the hash table elements.
        /// \details Calls the destructor of each of the LinkedKeys. As a result, chains created because of collisions
        /// will be deleted as well. Also deletes internal keys held by LinkedKeys individually, since the destructor
        /// of a LinkedKey does not.
        ~HashTable();

        /// \brief Finds and returns LinkedKey containing key given.
        /// \returns Pointer to LinkedKey with the given key, or nullptr if not found.
        /// \details Using LinkedKey facilitates traversing the chains created when collision occurs.
        ds::LinkedKey<T> *access(const T &key);

        /// \brief Inserts key given in internal array, or at the end of the chain if collision occurs.
        /// \details If key already exists, the entry will be overwritten.
        void insert(const T &key);

        /// \brief Removes entry for given key.
        /// \returns True if key was found and removed successfully.
        /// \details Appropriately handles deletions when key is part of a chain.
        bool remove(const T &key);

        /// \brief Prints the hash table.
        /// \details To indicate chaining, the sequence "->" is used.
        void print();

    private:
        const unsigned int M;
        LinkedKey<T> **internalArray;

    };

}

// Including necessary implementations of template structures and functions.
#include "../src/ds/AVLTree.tpp"
#include "../src/ds/HashTable.tpp"
#include "../src/ds/ds.tpp"

#endif //DS_H
