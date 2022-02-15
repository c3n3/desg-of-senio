#ifndef __GENAUTO_MAP_HPP__
#define __GENAUTO_MAP_HPP__

#include "StaticAllocator.hpp"

namespace genauto {
    template<typename T1, typename T2>
    struct Pair {
        Pair(T1 val) : one(val) {}
        Pair() : one(T1()), two(T2()){}
        Pair(T2 val) : two(val) {}
        Pair(T1 one, T2 two) : one(one), two(two) {}
        T1 one;
        T2 two; 
    };
    template<typename KT, typename VT, int N = 100>
    class Map {
    public:
        enum Result {
            Success,
            NoSpace,
            KeyNotFound,
            Failure
        };
    private:
        size_t size_;
        struct Node
        {
            Node() : left(nullptr), right(nullptr)
            {}
            Pair<KT, VT> pair;
            Node* left;
            Node* right;
        };

        StaticAllocator<Node, N> allocator;
        Node* tree_;

        Result insertRecursive(Node* add, Node* node)
        {
            if (node == nullptr) {
                return Failure;
            }
            // If less than go left
            if (add->pair.one < node->pair.one) {
                if (node->left == nullptr) {
                    node->left = add;
                    return Success;
                }
                return insertRecursive(add, node->left);
            }
            // Go right
            if (node->right == nullptr) {
                node->right = add;
                return Success;
            }
            return insertRecursive(add, node->right);
        }

        VT* getRecursive(KT& key, Node* node)
        {
            if (node == nullptr) {
                return nullptr;
            }
            if (node->pair.one == key) {
                return &node->pair.two;
            }
            if (key < node->pair.one) {
                return getRecursive(key, node->left);
            }
            return getRecursive(key, node->right);
        }

        Result removeRecursive(KT& key, Node** nodePtr)
        {
            Node* node = *nodePtr;
            if (node == nullptr) {
                return Failure;
            }
            if (key == node->pair.one) {
                if (node->left == nullptr) {
                    *nodePtr = node->right;
                    allocator.free(node);
                }
                Node* severance = node->right;
                // Replace node with left leaf
                *nodePtr = node->left;
                if (severance != nullptr) {
                    return insertRecursive(severance, *nodePtr);
                }
                return Success;
            }
            if (key < node->pair.one) {
                return removeRecursive(key, &(*nodePtr)->left);
            }
            return removeRecursive(key, &(*nodePtr)->right);
        }
    public:
        Map() : tree_(nullptr), size_(0)
        {}

        VT* get(KT& key)
        {
            return getRecursive(key, tree_);
        }

        bool contains(KT&& key)
        {
            return get(key) != nullptr;
        }

        Result insert(Pair<KT, VT>&& pair)
        {
            // If the root is null, we must init
            Node* newNode = allocator.alloc();
            if (newNode == nullptr) {
                return NoSpace;
            }
            newNode->pair = pair;
            if (tree_ == nullptr) {
                tree_ = newNode;
                size_++;
                return Success;
            }
            if (insertRecursive(newNode, tree_) == Failure) {
                allocator.free(newNode);
                return Failure;
            }
            size_++;
        }

        VT& operator[] (KT&& key)
        {
            VT* value = get(key);
            if (value == nullptr) {
                insert(Pair<KT, VT>(key));
            } else {
                return *value;
            }
            value = get(key);
            return *value;
        }

        VT& operator[] (KT& key)
        {
            VT* value = get(key);
            if (value == nullptr) {
                insert(Pair<KT, VT>(key));
            } else {
                return *value;
            }
            value = get(key);
            return *value;
        }

        Result remove(KT&& key)
        {
            Result res = removeRecursive(key, &tree_);
            if (res == Success)
            {
                size_--;
            }
            return res;
        }

        size_t size()
        {
            return size_;
        }
    };
}

#endif
