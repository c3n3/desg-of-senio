#ifndef __GENAUTO_STATIC_QUEUE_HPP__
#define __GENAUTO_STATIC_QUEUE_HPP__

#include "StaticAllocator.hpp"

namespace genauto {
    template<typename T, int N = 100>
    class StaticQueue {
    public:
        enum Result {
            Success,
            Failure
        };
    private:

        struct Node {
            Node() : next(nullptr), dequeued(false)
            {}
            T value;
            Node* next;
            bool dequeued;
        };
        StaticAllocator<Node, N> buf_;
        Node* head_;
        Result recursiveEnqueue(Node* node, T item)
        {
            if (node->next == nullptr) {
                Node* temp = buf_.alloc();
                if (temp == nullptr) return Failure;
                temp->value = item;
                node->next = temp;
                return Success;
            }
            return recursiveEnqueue(node->next, item);
        }
    public:
        StaticQueue() : head_(nullptr)
        {}

        Result enqueue(T item)
        {
            Result res;
            if (head_ == nullptr) {
                Node* temp = buf_.alloc();
                if (temp == nullptr) {
                    elog("Queue out of space\n");
                    res = Failure;
                } else {
                    temp->value = item;
                }
                head_ = temp;
                res = Success;
                goto Cleanup;
            }
            res = recursiveEnqueue(head_, item);
            Cleanup: ;
            Node* deq = head_;
            while (deq != nullptr && deq->dequeued) {
                Node* temp = deq;
                deq = deq->next;
                buf_.free(temp);
            }
            head_ = deq;
            return res;
        }

        Result dequeue(T& returnItem)
        {
            Node* node = head_;
            while (node != nullptr) {
                if (!node->dequeued) {
                    returnItem = node->value;
                    node->dequeued = true;
                    return Success;
                }
                node = node->next;
            }
            return Failure;
        }

        uint16_t count()
        {
            Node* node = head_;
            int count = 0;
            while (node != nullptr) {
                node = node->next;
                count++;
            }
        }

        int size()
        {
            return N;
        }
    };
}

#endif
