//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
#define PAXENGINE3_PROPERTYMALLOCALLOCATOR_H

#include "../Allocator.h"
#include <cstdlib>

namespace PAX {
    template<size_t ElementSize>
    class MallocAllocator : public Allocator<ElementSize> {
    public:
        void* allocate() override {
            return malloc(ElementSize);
        }

        void destroy(void * t) override {
            free(t);
        }
    };
}

#endif //PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
