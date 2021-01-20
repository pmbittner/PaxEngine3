//
// Created by paul on 20.08.18.
//

#ifndef PAXENGINE3_GLMINCLUDES_H
#define PAXENGINE3_GLMINCLUDES_H

#include "../macros/PlatformIncludes.h"
#include "polypropylene/stdutils/StringUtils.h"

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

//template <int D, typename T, glm::qualifier P>
//std::ostream &operator<<(std::ostream &os, glm::vec<D, T, P> v) {
//    return os << glm::to_string(v);
//}

namespace PAX {
    template<glm::length_t L, typename T, glm::qualifier Q>
    class TryParser<std::string, glm::vec<L, T, Q>> {
    public:
        static glm::vec<L, T, Q> tryParse(const std::string &str) {
            glm::vec<L, T, Q> ret(0);
            const size_t strlen = str.length();

            if (
                    (str[0] == '(' && str[strlen-1] == ')')
                    || (str[0] == '[' && str[strlen-1] == ']')
                    ) {
                std::string liststr = str.substr(1, strlen - 2);
                std::vector<std::string> numbers = String::split(',', liststr, false);

                const glm::length_t dims = glm::length_t(numbers.size());
                for (glm::length_t i = 0; i < L && i < dims; ++i)
                    ret[i] = String::tryParse<T>(numbers[i]);
            }

            return ret;
        }
    };
}

#endif //PAXENGINE3_GLMINCLUDES_H
