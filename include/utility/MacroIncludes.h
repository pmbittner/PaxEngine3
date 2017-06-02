//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

#define PAX_typeof(expr) std::type_index(typeid(expr))
#define PAX_nameof(type) std::type_index(typeid(type)).name()

#endif //PAXENGINE3_MACROINCLUDES_H
