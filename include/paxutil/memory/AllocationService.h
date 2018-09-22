//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
#define PAXENGINE3_PROPERTYALLOCATIONSERVICE_H

#include <assert.h>
#include <utility>
#include <unordered_set>
#include <memory>

#include "../datastructures/TypeMap.h"
#include "Allocator.h"
#include "allocators/MallocAllocator.h"

namespace PAX {
    class AllocationService {
        TypeMap<void*> _allocators;

        template<class Object>
        Allocator<Object>* getAllocatorFor() {
            if (_allocators.contains<Object>())
                return static_cast<Allocator<Object> *>(_allocators.get<Object>());
            return nullptr;
        }

    public:
        AllocationService() = default;

        template<class Object>
        bool registerAllocator(Allocator<Object> *provider) {
            return _allocators.put<Object>(provider);
        }

        template<class Object>
        size_t unregisterAllocator() {
            return _allocators.erase<Object>();
        }

        /**
         * This will return a new instance of the given Objecterty type.
         * If no provider for the given type is registered, a ObjectertyMallocAllocator will be registered as default.
         */
        template<class Object, typename... Args>
        std::shared_ptr<Object> create(Args... args) {
            Allocator<Object>* allocator = getAllocatorFor<Object>();

            if (!allocator) {
                allocator = new MallocAllocator<Object>();
                registerAllocator<Object>(allocator);
            }

            Object* memory = allocator->allocate();
            allocator->construct(memory, std::forward<Args>(args)...);

            return std::shared_ptr<Object>(memory, allocator->getDeleter());
        }
    };
}
#endif //PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
