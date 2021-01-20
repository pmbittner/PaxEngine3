//
// Created by Paul on 30.08.2018.
//

#ifndef PAXENGINE3_OSTREAMOVERLOADS_H
#define PAXENGINE3_OSTREAMOVERLOADS_H

#include <vector>
#include <ostream>
#include <polypropylene/reflection/TemplateTypeToString.h>

#include "../lib/GlmIncludes.h" // allows printing of glm types

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & v)
{
    os << "std::vector<" << PAX::Reflection::GetTypeName<T>() << ">[";
    for (const T & t : v)
        os << t;
    return os << "]";
}

#endif //PAXENGINE3_OSTREAMOVERLOADS_H
