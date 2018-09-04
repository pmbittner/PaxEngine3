//
// Created by Paul on 04.09.2018.
//

#ifndef PAXENGINE3_MAKEUNIQUE_H
#define PAXENGINE3_MAKEUNIQUE_H

/*
// If our cpp version is older than cpp14, define our own make_unique
#if __cplusplus < 201402L

#include <memory>

namespace std {
    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(forward<Args>(args)...));
    }
}

#endif
 */

#endif //PAXENGINE3_MAKEUNIQUE_H
