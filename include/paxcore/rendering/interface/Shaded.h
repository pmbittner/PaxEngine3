//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SHADED_H
#define PAXENGINE3_SHADED_H

#include <memory>

#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class Shaded {
    public:
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader) = 0;
    };
}

#endif //PAXENGINE3_SHADED_H
