#ifndef __GENAUTO_QUEUE_HPP__
#define __GENAUTO_QUEUE_HPP__

namespace genauto {
    template<typename T>
    class Queue {
        T* buffer_;
        uint16_t n;
        uint16_t head_;
        uint16_t tail_;
        uint16_t count_;
    public:
        enum Result {
            Success,
            Failure
        };

        Queue(int n) : count_(0), head_(0), tail_(0), n(n)
        {
            buffer_ = new T[n];
        }

        ~Queue()
        {
            delete[] buffer_;
        }

        Result enqueue(T item)
        {
            if (count_ != n) {
                buffer_[head_] = item;
                count_++;
                head_ = (head_ + 1) % n;
                return Success;
            }
            return Failure;
        }

        Result dequeue(T& returnItem)
        {
            if (count_ != 0) {
                returnItem = buffer_[tail_];
                tail_ = (tail_ + 1) % n;
                count_--;
                return Success;
            }
            return Failure;
        }

        uint16_t count()
        {
            return count_;
        }

        int size()
        {
            return n;
        }
    };
}

#endif
