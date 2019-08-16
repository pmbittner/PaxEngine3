//
// Created by Paul on 13.08.2019.
//

#ifndef PAXENGINE3_PROPERTYOWNINGSYSTEM_H
#define PAXENGINE3_PROPERTYOWNINGSYSTEM_H

#include <paxutil/memory/allocators/PoolAllocator.h>
#include "WorldSystem.h"

namespace PAX {
    template<class P>
    class PropertyOwningSystem : public WorldSystem {
        PoolAllocator<sizeof(P)> allocator;

    public:
        struct Iterator {
        private:
            typename PoolAllocator<sizeof(P)>::MemoryChunk * current = nullptr;

            inline bool isCurrentValid() {
                return current->allocated && reinterpret_cast<P*>(&(current->data))->isActive();
            }

        public:
            explicit Iterator(typename PoolAllocator<sizeof(P)>::MemoryChunk * pos)
                : current(pos)
            {
                if (!isCurrentValid()) {
                    this->operator++();
                }
            }

            Iterator & operator=(const Iterator & other) = default;

            inline bool operator==(const Iterator & other) {
                return current == other.current;
            }

            inline bool operator!=(const Iterator & other) {
                return !operator==(other);
            }

            P* operator*() {
                return reinterpret_cast<P*>(&(current->data));
            }

            Iterator & operator++() {
                do {
                    ++current;
                } while (!isCurrentValid());

                return *this;
            }
        };

        PropertyOwningSystem() = default;

        void initialize(Game *game) override {
            WorldSystem::initialize(game);

            AllocationService & allocationService = P::Container::GetPropertyAllocator();
            allocationService.registerAllocator(paxtypeid(P), &allocator);
        }

        Iterator begin() { return Iterator(allocator.getMemory()); }
        Iterator end() { return  Iterator(allocator.getMemory() + allocator.getCapacity()); }
        //Iterator begin() const { return _map.begin(); }
        //Iterator end() const { return _map.end(); }
    };
}

#endif //PAXENGINE3_PROPERTYOWNINGSYSTEM_H
