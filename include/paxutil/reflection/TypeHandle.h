//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_TYPEINFO_H
#define PAXENGINE3_TYPEINFO_H

#include <typeindex>

namespace PAX {
    using TypeHandle = std::type_index;
#define paxtypeof(T) TypeHandle(typeid(T))
}

#endif //PAXENGINE3_TYPEINFO_H
