//
// Created by Bittner on 14/08/2019.
//

#ifndef PAXENGINE3_POOLALLOCATOR_H
#define PAXENGINE3_POOLALLOCATOR_H

#include "../Allocator.h"
#include <paxutil/log/Log.h>

namespace PAX {
    template<size_t ElementSize>
    class PoolAllocator : public Allocator<ElementSize> {
        static constexpr size_t Initial_Size = 1024;

        union MemoryChunk {
            // Do not change member layout because
            // 'data' has to be at the same address as the MemoryChunk itself.
            char data[ElementSize];
            int64_t next = -1;
        };

        MemoryChunk * memory = nullptr;
        size_t capacity = 0;
        int64_t nextFree = -1;

    public:
        explicit PoolAllocator(size_t capacity = Initial_Size) : capacity(capacity) {
            memory = new MemoryChunk[capacity];
            clear();
        }

        PoolAllocator(const PoolAllocator & other) = delete;
        PoolAllocator(const PoolAllocator&& other) = delete;
        PoolAllocator & operator=(const PoolAllocator & other) = delete;
        PoolAllocator & operator=(const PoolAllocator&& other) = delete;

        ~PoolAllocator() override {
            delete[] memory;
        }

        void * allocate() override {
            MemoryChunk * mem = memory + nextFree;
            if (mem->next >= 0) {
                nextFree = mem->next;
            }
            return &(mem->data);
        };

        void destroy(void * size) override {
            // size is a pointer to the data inside a memory chunk.
            // Because data is at the beginning of a MemoryChunk we should be able to safely cast it.
            MemoryChunk * mem = reinterpret_cast<MemoryChunk*>(size);
            if (memory <= mem && mem < memory + capacity) {
                mem->next = nextFree;
                nextFree = mem - memory;
            } else {
                // The data seems not to be allocated by us.
                // We should not throw an exception as this function is likely to be called in destructors.
                PAX_LOG(PAX::Log::Level::Error, "Given pointer (" << size << ") was not allocated by me!");
            }
        };

        void clear() {
            for (uint64_t i = 0; i < capacity - 1; ++i) {
                memory[i].next = i + 1;
            }
            nextFree = 0;
        }
    };
}

#endif //PAXENGINE3_POOLALLOCATOR_H
