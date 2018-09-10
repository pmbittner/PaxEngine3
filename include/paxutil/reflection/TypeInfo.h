//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_TYPEINFO_H
#define PAXENGINE3_TYPEINFO_H

#include <typeindex>

namespace PAX {
    namespace Reflection {
        template<typename Type>
        inline std::type_index GetType() {
            return std::type_index(typeid(Type));
        }
    }
}

#endif //PAXENGINE3_TYPEINFO_H
