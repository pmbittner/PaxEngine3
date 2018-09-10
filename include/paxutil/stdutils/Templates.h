//
// Created by Paul on 20.12.2017.
//

#ifndef PAXENGINE3_TEMPLATES_H
#define PAXENGINE3_TEMPLATES_H

#include <algorithm>

namespace PAX {
    namespace Util {
        template<bool B, class T, class F>
        using conditional_t_cpp14 = typename std::conditional<B, T, F>::type;
    }
}

#endif //PAXENGINE3_TEMPLATES_H
