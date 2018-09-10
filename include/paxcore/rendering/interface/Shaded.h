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
        virtual void registerFlags(Shader::Flags &flags) {};
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader) {};
    };
}

#endif //PAXENGINE3_SHADED_H
