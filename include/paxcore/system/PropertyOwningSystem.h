//
// Created by Paul on 13.08.2019.
//

#ifndef PAXENGINE3_PROPERTYOWNINGSYSTEM_H
#define PAXENGINE3_PROPERTYOWNINGSYSTEM_H

#include <paxutil/memory/Allocator.h>

namespace PAX {
    template<class P>
    class PropertyOwningSystem : public Allocator {
        static constexpr size_t Initial_Size = 1000;

        struct MemoryChunk {
            bool allocated = false;
            union {
                P property;
                struct {
                    size_t prev = 0;
                    size_t next = 0;
                };
            };
        };

        MemoryChunk * memory = nullptr;
        size_t capacity = 0;
        size_t nextFree = 0;

    public:
        explicit PropertyOwningSystem(size_t capacity = Initial_Size) : capacity(capacity) {
            clear();
        }

        ~PropertyOwningSystem() override {
            delete[] memory;
        }

        void * allocate(size_t size) override {
            MemoryChunk * mem = memory[nextFree];
            nextFree = mem->next;

            {
                MemoryChunk * prev = memory[mem->prev];
                prev->next = nextFree;
                nextFree->prev = prev;
            }

            // Is this necessary?
            mem->next = 0;
            mem->prev = 0;

            return &(mem->property);
        };

        void destroy(void * size) override {

        };

        void clear() {
            delete[] memory;
            memory = new MemoryChunk[capacity];
            nextFree = 0;

            for (size_t i = 0; i < capacity; ++i) {
                memory[i].prev = (i - 1) % capacity;
                memory[i].next = (i + 1) % capacity;
            }
        }
    };
}

#endif //PAXENGINE3_PROPERTYOWNINGSYSTEM_H
