//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
#define PAXENGINE3_PROPERTYALLOCATIONSERVICE_H


#include "paxutil/reflection/TypeMap.h"

#include "Allocator.h"
#include "allocators/MallocAllocator.h"
#include "allocators/PoolAllocator.h"

namespace PAX {
    class AllocationService {
        TypeMap<IAllocator*> allocators;

    public:
        AllocationService() = default;

        void registerAllocator(const TypeHandle& type, IAllocator * provider) {
            allocators[type] = provider;
        }

        size_t unregisterAllocator(const TypeHandle & type) {
            return allocators.erase(type);
        }

        template<class T>
        void * allocate() {
            Allocator<sizeof(T)> * allocator = nullptr;

            const auto & allocIt = allocators.find(paxtypeid(T));
            if (allocIt != allocators.end()) {
                allocator = dynamic_cast<Allocator<sizeof(T)>*>(allocIt->second);
                if (!allocator) {
                    PAX_LOG(PAX::Log::Level::Error, "Registered Allocator for " << typeid(T).name() << " is not of type Allocator<" << typeid(T).name() << ">!");
                }
            }

            if (!allocator){
                // TODO: Avoid new: Allocator for allocator lul
                allocator = new PoolAllocator<sizeof(T)>();
                registerAllocator(paxtypeid(T), allocator);
            }

            return allocator->allocate();
        }

        bool free(const TypeHandle& type, void * object) {
            const auto& allocator = allocators.find(type);
            if (allocator != allocators.end()) {
                allocator->second->destroy(object);
                return true;
            }

            return false;
        }


        /**
         * This will return a new instance of the given Objecterty type.
         * If no provider for the given type is registered, a MallocAllocator will be registered as default.
         */
        /*template<class Object, typename... Args>
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
        }//*/

        /**
         * This should become standard later.
         * TODO: Replace this with alloc later on
         */
        /*template<class Object>
        void* createNoArgs() {
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
            return memory;
        }

        // TODO: Replace this with free later on
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
        //*/
    };
}
#endif //PAXENGINE3_PROPERTYALLOCATIONSERVICE_H
