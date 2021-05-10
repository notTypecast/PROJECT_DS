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

    template<typename T>
    struct AVLNode {
        T key;
        AVLNode *left;
        AVLNode *right;
        AVLNode *same;
        int height;
    };

    //TODO: mention that LinkedKey's destructor is responsible for deleting next, but not key
    template <typename T>
    struct LinkedKey {
        LinkedKey();
        LinkedKey(T *key, LinkedKey<T> *next);
        ~LinkedKey();
        T *key;
        LinkedKey *next;
    };

    template<typename T>
    struct AVLNode<T> *createAVLNode(const T &key);

    template <typename T>
    LinkedKey<T>* createLinkedKey(AVLNode<T>* node);

    // delete linked key without deleting chain
    template <typename T>
    /// \details Safely detaches and deletes LinkedKey.
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
        ds::LinkedKey<T>* access(const T &key);

        void insert(const T &key);

        bool remove(const T &key);

        ds::LinkedKey<T>* getMinKey();

        ds::LinkedKey<T>* getMaxKey();

        void printInOrder();

    private:
        struct AVLNode<T> *root;
        bool KEYFOUND;

        void printInOrderRecursively(ds::AVLNode<T> *currentNode);

        int getNodeHeight(ds::AVLNode<T> *node);

        int getNodeBalanceFactor(ds::AVLNode<T> *node);

        AVLNode<T> *insertAtNode(AVLNode<T> *node, AVLNode<T> *newNode);

        AVLNode<T> *removeAtNode(AVLNode<T> *node, const T &key);

        AVLNode<T> *rightRotate(AVLNode<T> *node);

        AVLNode<T> *leftRotate(AVLNode<T> *node);

        AVLNode<T> *getSmallestNode(AVLNode<T> *subRoot);

        void deleteNode(AVLNode<T> *node);
    };

    template <typename T>
    class HashTable {
    public:
        HashTable(unsigned int M);
        ~HashTable();
        ds::LinkedKey<T>* access(const T &key);
        void insert(const T &key);
        bool remove(const T &key);
        void print();

    private:
        const unsigned int M;
        LinkedKey<T> *internalArray;

    };

}

#include "../src/ds/AVLTree.tpp"
#include "../src/ds/HashTable.tpp"
#include "../src/ds/ds.tpp"

#endif //DS_H
