#ifndef __GENAUTO_STATIC_LIST_HPP__
#define __GENAUTO_STATIC_LIST_HPP__

namespace genauto {
    template<typename T>
    class StaticList {
        const T* list;
        const uint16_t size;
    public:
        StaticList(T* input, uint16_t size)
            : list(input), size(size)
        {}
        const T* getList()
        {
            return list;
        }

        const uint16_t getSize()
        {
            return size;
        }

        const T& operator[](uint16_t i)
        {
            return list[i];
        }
    };
}

#endif
