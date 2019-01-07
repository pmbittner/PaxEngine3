//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
#define PAXENGINE3_PROPERTYALLOCATIONSERVICE_H

#include <assert.h>
#include <utility>
#include <unordered_set>
#include <memory>

#include "paxutil/reflection/TypeMap.h"
#include "Allocator.h"
#include "allocators/MallocAllocator.h"

namespace PAX {
    template<class Object, class AllocType>
    class TypedAllocator : public AllocType {
    public:
        void destroy(void * size) override {
            // static_cast is used, as we ensure, that size is always of type object, but dynamic_cast would be correct here.
            static_cast<Object*>(size)->~Object();
            AllocType::destroy(size);
        };
    };

    class AllocationService {
        TypeMap<Allocator*> _allocators;

    public:
        AllocationService() = default;

        void registerAllocator(const TypeHandle& type, Allocator * provider) {
            _allocators[type] = provider;
        }

        size_t unregisterAllocator(const TypeHandle & type) {
            return _allocators.erase(type);
        }

        /**
         * This will return a new instance of the given Objecterty type.
         * If no provider for the given type is registered, a MallocAllocator will be registered as default.
         */
        template<class Object, typename... Args>
        Object* create(Args&&... args) {
            TypeHandle objectType = paxtypeof(Object);
            Allocator* allocator;

            const auto & allocIt = _allocators.find(objectType);
            if (allocIt == _allocators.end()) {
                allocator = new TypedAllocator<Object, MallocAllocator>();
                registerAllocator(objectType, allocator);
            } else {
                allocator = allocIt->second;
            }

            void* memory = allocator->allocate(sizeof(Object));
            Object * object = new (memory) Object(std::forward<Args>(args)...);

            return object;
        }

        bool destroy(const TypeHandle& type, void* object) {
            // FIXME: Per default, the allocators will not call the destructor on object!
            //        This works for now because the default allocator does that with a trick.
            const auto& allocator = _allocators.find(type);
            if (allocator != _allocators.end()) {
                allocator->second->destroy(object);
                return true;
            }

            return false;
        }
    };
}
#endif //PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
