//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
#define PAXENGINE3_PROPERTYMALLOCALLOCATOR_H

#include "../Allocator.h"
#include <cstdlib>

namespace PAX {
    class MallocAllocator : public Allocator {
    public:
        void* allocate(size_t size) override {
            return malloc(size);
        }

        void destroy(void * t) override {
            free(t);
        }
    };
}

#endif //PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
