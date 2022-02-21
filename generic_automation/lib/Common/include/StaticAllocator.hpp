#ifndef __GENAUTO_STATIC_ALLOCATOR_HPP__
#define __GENAUTO_STATIC_ALLOCATOR_HPP__

#include <stddef.h>
#include <stdint.h>
#include "Defines.hpp"

namespace genauto {
    template<typename T, int N>
    class StaticAllocator {
        struct BuffNode
        {
            BuffNode() : free(true)
            {}
            T value;
            bool free;
        };
        BuffNode buffer_[N];
    public:
        T* alloc()
        {
            for (int i = 0; i < ARRSIZE(buffer_); i++) {
                if (buffer_[i].free) {
                    buffer_[i].free = false;
                    return &buffer_[i].value;
                }
            }
            return nullptr;
        }

        void free(T* value)
        {
            BuffNode* node = (BuffNode*)(((uint8_t*)value) - offsetof(BuffNode, value));
            node->free = true;
        }
    };
}

#endif
