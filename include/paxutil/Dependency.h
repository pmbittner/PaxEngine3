//
// Created by Paul on 16.07.2017.
//

#ifndef PAXENGINE3_DEPENDENCY_H
#define PAXENGINE3_DEPENDENCY_H

namespace PAX {
    template<class T>
    class Dependency {
    public:
        virtual bool met(const T &t) const {
            // empty dependency is always fullfilled
            return true;
        }
    };
}

#endif //PAXENGINE3_DEPENDENCY_H
