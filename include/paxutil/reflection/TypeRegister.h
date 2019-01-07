//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_TYPEREGISTER_H
#define PAXENGINE3_TYPEREGISTER_H

#include "TypeMap.h"

namespace PAX {
    class TypeRegister {
        TypeMap<void*> factories;

    public:
        TypeRegister();
        void set(const TypeHandle & type, void* factory);

        template<typename T>
        T* get() {
            const auto& factory = factories.find(paxtypeid(T));
            if (factory != factories.end())
                return static_cast<T*>(factory->second);
            return nullptr;
        }
    };
}

#endif //PAXENGINE3_TYPEREGISTER_H
