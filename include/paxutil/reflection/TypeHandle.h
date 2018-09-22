//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_TYPEINFO_H
#define PAXENGINE3_TYPEINFO_H

#include <typeindex>

namespace PAX {
    typedef std::type_index TypeHandle;
    namespace Reflection {

        template<typename Type>
        inline TypeHandle GetType() {
            return TypeHandle(typeid(Type));
        }
    }
}

#endif //PAXENGINE3_TYPEINFO_H
