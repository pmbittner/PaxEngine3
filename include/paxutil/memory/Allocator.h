//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYALLOCATOR_H
#define PAXENGINE3_PROPERTYALLOCATOR_H

#include <utility>

namespace PAX {
    template<class Prop>
    class Allocator {
    public:
        virtual ~Allocator() = default;

        template<typename... Args>
        Prop* construct(Prop* component, Args... args) {
            return new (component) Prop(std::forward<Args>(args)...);
        }

        virtual Prop* allocate() = 0;
        virtual void (*getDeleter(void))(Prop*) = 0;
    };
}

#endif //PAXENGINE3_PROPERTYALLOCATOR_H
