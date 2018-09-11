//
// Created by paul on 20.08.18.
//

#ifndef PAXENGINE3_GLMINCLUDES_H
#define PAXENGINE3_GLMINCLUDES_H

#include "../macros/PlatformIncludes.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>

#include <ostream>

template <template <typename, glm::qualifier> class matType, typename T, glm::qualifier P>
std::ostream& operator<<(std::ostream& os, matType<T, P> const & x)
{
    return os << glm::to_string(x);
}

template <template <int, typename, glm::qualifier> class matType, int dims, typename T, glm::qualifier P>
std::ostream& operator<<(std::ostream& os, matType<dims, T, P> const & x)
{
    return os << glm::to_string(x);
}

template <template <int, int, typename, glm::qualifier> class matType, int dims0, int dims1, typename T, glm::qualifier P>
std::ostream& operator<<(std::ostream& os, matType<dims0, dims1, T, P> const & x)
{
    return os << glm::to_string(x);
}

#endif //PAXENGINE3_GLMINCLUDES_H
