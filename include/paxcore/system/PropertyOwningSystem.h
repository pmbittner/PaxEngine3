//
// Created by Paul on 13.08.2019.
//

#ifndef PAXENGINE3_PROPERTYOWNINGSYSTEM_H
#define PAXENGINE3_PROPERTYOWNINGSYSTEM_H

#include <paxutil/memory/Allocator.h>

namespace PAX {
    template<class P>
    class PropertyOwningSystem : public Allocator {
        static constexpr size_t Initial_Size = 1024;

        struct MemoryChunk {
            bool allocated = false;
            union {
                P property;
                struct {
                    long next = -1;
                };
            };
        };

        MemoryChunk * memory = nullptr;
        size_t capacity = 0;
        long nextFree = -1;

    public:
        explicit PropertyOwningSystem(size_t capacity = Initial_Size) : capacity(capacity) {
            clear();
        }

        PropertyOwningSystem(const PropertyOwningSystem & other) = delete;
        PropertyOwningSystem(const PropertyOwningSystem&& other) = delete;
        PropertyOwningSystem & operator=(const PropertyOwningSystem & other) = delete;
        PropertyOwningSystem & operator=(const PropertyOwningSystem&& other) = delete;

        ~PropertyOwningSystem() override {
            delete[] memory;
        }

        void * allocate(size_t size) override {
            MemoryChunk * mem = memory[nextFree];
            nextFree = mem->next;

            /*
            if (mem->prev >= 0) {
                MemoryChunk * prev = memory[mem->prev];
                prev->next = nextFree;
                nextFree->prev = prev;
            }*/

            // Is this necessary?
            mem->next = -1;
            //mem->prev = 0;

            return &(mem->property);
        };

        void destroy(void * size) override {
            MemoryChunk * mem = reinterpret_cast<MemoryChunk*>(size);
        };

        void clear() {
            delete[] memory;
            memory = new MemoryChunk[capacity];
            nextFree = 0;

            for (size_t i = 0; i < capacity - 1; ++i) {
                memory[i].next = i + 1;
                memory[i + 1].prev = i;
            }
        }
    };
}

#endif //PAXENGINE3_PROPERTYOWNINGSYSTEM_H
