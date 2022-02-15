#ifndef __GENAUTO_STATIC_QUEUE_HPP__
#define __GENAUTO_STATIC_QUEUE_HPP__

namespace genauto {
    template<typename T, int N = 10>
    class Queue {
        T buffer_[N];
        uint16_t head_;
        uint16_t tail_;
        uint16_t count_;
    public:
        enum Result {
            Success,
            Failure
        };

        Queue() : count_(0), head_(0), tail_(0)
        {}

        Result enqueue(T&& item)
        {
            if (count_ != N) {
                buffer_[head_] = item;
                count_++;
                head_ = (head_ + 1) % N;
                return Success;
            }
            return Failure;
        }

        Result dequeue(T& returnItem)
        {
            if (count_ != 0) {
                returnItem = buffer_[tail_];
                tail_ = (tail_ + 1) % N;
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
            return N;
        }
    };
}

#endif
