#ifndef __GENAUTO_MAP_HPP__
#define __GENAUTO_MAP_HPP__

#include "StaticAllocator.hpp"
#include <iostream>

namespace genauto {
    template<typename T1, typename T2>
    struct Pair {
        Pair(T1 val) : one(val) {}
        Pair() : one(T1()), two(T2()){}
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

        const Result SUCCESS = Success;
        const Result NO_SPACE = NoSpace;
        const Result KEY_NOT_FOUND = KeyNotFound;
        const Result FAILURE = Failure;

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

        Node* index(int& i, Node* node) const
        {
            if (i >= size_) {
                return nullptr;
            }
            if (node != nullptr) {
                if (i == 0) {
                    return node;
                }
                i--;
                auto val = index(i, node->left);
                if (val) {
                    return val;
                } else {
                    return index(i, node->right);
                }
            }
            return nullptr;
        }
        
    public:

        Map() : tree_(nullptr), size_(0)
        {}

        Pair<KT, VT>* index(int i) const
        {
            Node* val = index(i, tree_);
            if (val) {
                return &val->pair;
            }
            return nullptr;
        }

        VT* get(KT& key)
        {
            return getRecursive(key, tree_);
        }

        bool contains(KT key)
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

        Result insert(KT k, VT v)
        {
            // If the root is null, we must init
            Pair<KT, VT> pair(k, v);
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

        Result remove(KT key)
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

        class Iterator {
            const Map<KT, VT>* map_;
            int i;
        public:
            Iterator(const Map<KT, VT>* map, int index) : map_(map), i(index)
            {}

            Pair<KT, VT>& operator*() const
            {
                return *map_->index(i);
            }

            Pair<KT, VT>* operator->()
            {
                return map_->index(i);
            }

            Iterator& operator++() { i++; return *this; }  

            // Postfix increment
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b)
            {
                return a.i == b.i && a.map_ == b.map_;
            };
            friend bool operator!= (const Iterator& a, const Iterator& b)
            {
                return !(a == b);
            }; 
        };


        Iterator begin() const
        {
            return Iterator(this, 0);
        }

        Iterator end()
        {
            return Iterator(this, size());
        }
    };
}

#endif
