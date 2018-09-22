//
// Created by paul on 22.09.18.
//

#ifndef PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
#define PAXENGINE3_PROPERTYMALLOCALLOCATOR_H

#include "../Allocator.h"
#include <cstdlib>

namespace PAX {
    template<class Prop>
    class MallocAllocator : public Allocator<Prop> {
        static void del(Prop* p) {
            p->~Prop();
            free(p);
        }

    public:
        virtual Prop* allocate() override {
            return static_cast<Prop*>(malloc(sizeof(Prop)));
        }

        virtual void (*getDeleter(void))(Prop*) override {
            return &del;
        }
    };
}

#endif //PAXENGINE3_PROPERTYMALLOCALLOCATOR_H
