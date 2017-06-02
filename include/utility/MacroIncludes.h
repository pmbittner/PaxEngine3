//
// Created by Paul on 02.06.2017.
//

#ifndef PAXENGINE3_MACROINCLUDES_H
#define PAXENGINE3_MACROINCLUDES_H

#define PAX_typeof(expr) std::type_index(typeid(expr))
#define PAX_nameof(type) std::type_index(typeid(type)).name()

#define PAX_notnull(value, str_message) if (value == nullptr) throw std::invalid_argument(str_message);

#endif //PAXENGINE3_MACROINCLUDES_H
