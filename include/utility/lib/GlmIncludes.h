//
// Created by paul on 20.08.18.
//

#ifndef PAXENGINE3_GLMINCLUDES_H
#define PAXENGINE3_GLMINCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/ext.hpp>

#include <ostream>

template <template <typename, glm::precision> class matType, typename T, glm::precision P>
std::ostream& operator<<(std::ostream& os, matType<T, P> const & x)
{
    return os << glm::to_string(x);
}

#endif //PAXENGINE3_GLMINCLUDES_H
