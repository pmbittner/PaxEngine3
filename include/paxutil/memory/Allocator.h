//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYALLOCATOR_H
#define PAXENGINE3_PROPERTYALLOCATOR_H

#include <utility>

namespace PAX {
    class Allocator {
    public:
        virtual ~Allocator() = default;
        virtual void* allocate(size_t size) = 0;
        virtual void destroy(void * size) = 0;
    };
}

#endif //PAXENGINE3_PROPERTYALLOCATOR_H
