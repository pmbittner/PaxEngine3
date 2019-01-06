//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_TYPEINFO_H
#define PAXENGINE3_TYPEINFO_H

#include <typeindex>

namespace PAX {
    using TypeHandle = std::type_index;
}

#define paxtypeid(T) typeid(T)
#define paxtypeof(T) PAX::TypeHandle(paxtypeid(T))

#endif //PAXENGINE3_TYPEINFO_H
