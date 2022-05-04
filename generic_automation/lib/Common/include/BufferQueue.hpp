#ifndef __GENAUTO_BUFFER_QUEUE_HPP__
#define __GENAUTO_BUFFER_QUEUE_HPP__

#include "StaticAllocator.hpp"
#include "Log.hpp"
#include <string.h>

namespace genauto {
    struct Buffer {
        uint8_t* buffer;
        size_t size;
    };

    template <int BUF_SIZE, int BUF_COUNT>
    class BufferQueue {
    private:
        struct Node {
            Node() : next(nullptr), dequeued(false), size(0)
            {}
            uint8_t value[BUF_SIZE];
            size_t size;
            Node* next;
            bool dequeued;
            void set(uint8_t* mem, size_t sizeIn)
            {
                if (sizeIn > BUF_SIZE) {
                    elog("Input size %d too great for buffer size %d\n", sizeIn, BUF_SIZE);
                    return;
                }
                memcpy(value, mem, sizeIn);
                size = sizeIn;
            }
        };
        StaticAllocator<Node, BUF_COUNT> buf_;
        Node* head_;

        bool recursiveEnqueue(Node* node, uint8_t* item, size_t size)
        {
            if (node->next == nullptr) {
                Node* temp = buf_.alloc();
                if (temp == nullptr) {
                    elog("Error out of space\n");
                    return false;   
                }
                temp->set(item, size);
                temp->dequeued = false;
                node->next = temp;
                return true;
            }
            return recursiveEnqueue(node->next, item, size);
        }

    public:
        BufferQueue() : head_(nullptr)
        {}

        bool enqueue(uint8_t* item, size_t size)
        {
            bool res;
            if (head_ == nullptr) {
                Node* temp = buf_.alloc();
                if (temp == nullptr) {
                    elog("Queue out of space\n");
                    res = false;
                } else {
                    temp->set(item, size);
                }
                temp->dequeued = false;
                head_ = temp;
                res = true;
                goto Cleanup;
            }
            res = recursiveEnqueue(head_, item, size);
            Cleanup: ;
            Node* deq = head_;
            while (deq != nullptr && deq->dequeued) {
                Node* temp = deq;
                deq = deq->next;
                temp->next = nullptr;
                buf_.free(temp);
            }
            head_ = deq;
            return res;
        }

        bool front(Buffer& returnItem)
        {
            Node* node = head_;
            while (node != nullptr) {
                if (!node->dequeued) {
                    returnItem.buffer = node->value;
                    returnItem.size = node->size;
                    return true;
                }
                node = node->next;
                //dlog("dequeue\n");
            }
            return false;
        }

        void dequeue()
        {
            Node* node = head_;
            while (node != nullptr) {
                if (!node->dequeued) {
                    node->dequeued = true;
                    return;
                }
                node = node->next;
            }
        }

        uint16_t count()
        {
            Node* node = head_;
            int count = 0;
            while (node != nullptr) {
                node = node->next;
                count++;
            }
            return count;
        }

        int size()
        {
            return BUF_COUNT;
        }
    };
}

#endif
