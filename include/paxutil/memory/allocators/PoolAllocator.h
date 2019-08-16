//
// Created by Bittner on 14/08/2019.
//

#ifndef PAXENGINE3_POOLALLOCATOR_H
#define PAXENGINE3_POOLALLOCATOR_H

#include "../Allocator.h"
#include <paxutil/log/Errors.h>

namespace PAX {
    /// A PoolAllocator of fixed capacity.
    /// It can neither grow nor shrink.
    /// \tparam ElementSize The size in bytes an allocatable element should have.
    template<size_t ElementSize>
    class PoolAllocator : public Allocator<ElementSize> {
    public:
        static constexpr size_t Initial_Size = 1024;

        struct MemoryChunk {
            static constexpr int32_t DataOffset = sizeof(bool);
            bool allocated = false;
            char data[ElementSize];
        };

    private:
        MemoryChunk * memory = nullptr;
        size_t capacity = 0;

        /// This is a stack to remember which MemoryChunks are free.
        /// The stack is realised as an array where the top is at the beginning and is moved to the back as elements get popped.
        /// Hence, when an element is pushed, topIndex is decremented.
        struct {
            int32_t * stack;
            int32_t topIndex;
        } freeChunks;

        int32_t numberOfAllocations = 0;

    public:
        /// Creates a PoolAllocator of fixedSize.
        /// \param capacity The maximum number of elements that can be allocated simultaneously.
        explicit PoolAllocator(size_t capacity = Initial_Size) : capacity(capacity), numberOfAllocations(0) {
            memory = new MemoryChunk[capacity];
            freeChunks.stack = new int32_t[capacity];
            clear();
        }

        PoolAllocator(const PoolAllocator & other) = delete;
        PoolAllocator(const PoolAllocator&& other) = delete;
        PoolAllocator & operator=(const PoolAllocator & other) = delete;
        PoolAllocator & operator=(const PoolAllocator&& other) = delete;

        ~PoolAllocator() override {
            if (numberOfAllocations > 0) {
                PAX_LOG(PAX::Log::Level::Warn, "Deleting PoolAllocator although there are still " << numberOfAllocations << " elements allocated!");
            }

            delete[] memory;
            delete[] freeChunks.stack;
        }

        void * allocate() override {
            if (freeChunks.topIndex < capacity) {
                ++numberOfAllocations;

                int32_t ourChunk = freeChunks.stack[freeChunks.topIndex];
                ++freeChunks.topIndex;

                MemoryChunk * mem = memory + ourChunk;
                mem->allocated = true;
                return &(mem->data);
            } else {
                PAX_THROW_RUNTIME_ERROR("Memory overflow");
            }
        };

        void destroy(void * data) override {
            // The given pointer points to the data inside a MemoryChunk.
            // MemoryChunk::DataOffset describes the byte offset of this data.
            // Using it allows us to jumpt to the start of the MemoryChunk.
            MemoryChunk * chunkToFree = reinterpret_cast<MemoryChunk*>(((char*)data) - MemoryChunk::DataOffset);

            // On a 64bit machine (chunkToFree - memory) is of type int64, but as it is just an offset in our array
            // it should be small, wherefore we just cast int to int32_t.
            const int32_t memIndex = static_cast<int32_t>(chunkToFree - memory);

            if (0 <= memIndex && memIndex < capacity) {
                if (chunkToFree->allocated) {
                    chunkToFree->allocated = false;
                    --numberOfAllocations;

                    // Decrement the topIndex to make space for our new memIndex, as it is also a free chunk now.
                    --freeChunks.topIndex;
                    // Insert such that the stack is sorted and the smallest index stays at the stack top.
                    // Possible optimisation: The stack needs not to be sorted. We only need the smallest element of the stack at the front.
                    int32_t posToInsertFreeIndex = freeChunks.topIndex;
                    while (freeChunks.stack[posToInsertFreeIndex + 1] < memIndex) {
                        freeChunks.stack[posToInsertFreeIndex] = freeChunks.stack[freeChunks.topIndex];
                        ++posToInsertFreeIndex;
                    }

                    freeChunks.stack[posToInsertFreeIndex] = memIndex;
                } else {
                    PAX_LOG(PAX::Log::Level::Warn, "Trying to free unallocated memory chunk! aborting...");
                }
            } else {
                // The data seems not to be allocated by us.
                // We should not throw an exception as this function is likely to be called in destructors.
                PAX_LOG(PAX::Log::Level::Error, "Given pointer (" << data << ") was not allocated by me!");
            }
        };

        void clear() {
            if (numberOfAllocations == 0) {
                // Null memory (Thereby set allocated to false in all chunks).
                memset(memory, 0, capacity * sizeof(MemoryChunk));

                // Initialise free chunks stack: All chunks are free now.
                freeChunks.topIndex = 0;
                for (uint32_t i = 0; i < capacity; ++i) {
                    freeChunks.stack[i] = i;
                }
            } else {
                PAX_LOG(PAX::Log::Level::Error, "Clearing PoolAllocator although there are still " << numberOfAllocations << " elements allocated");
            }
        }

        /// Do not alter the memory!
        /// We hand it to you in trust for iterating only!
        MemoryChunk * getMemory() {
            return memory;
        }

        size_t getCapacity() {
            return capacity;
        }
    };
}

#endif //PAXENGINE3_POOLALLOCATOR_H
