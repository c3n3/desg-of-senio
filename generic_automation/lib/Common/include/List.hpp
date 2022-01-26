#ifndef __GENAUTO_LIST_HPP__
#define __GENAUTO_LIST_HPP__

namespace genauto {
    template<typename T>
    class List {
    private:
        T* buffer_;
        uint16_t size_;
        uint16_t count_;
    public:
        List(int startingSize) : size_(startingSize), count_(0)
        {
            buffer_ = new T[size_];
        }

        void pushBack(T&& item)
        {
            buffer_[count_] = item;
            count_++;
        }

        T& operator[](uint16_t pos)
        {
            return buffer_[pos];
        }

        T* begin()
        {
            return &buffer_[0];
        }

        T* end()
        {
            return &buffer_[count_];
        }
    };
}

#endif
