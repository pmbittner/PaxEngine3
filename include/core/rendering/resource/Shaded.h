//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SHADEDNODE_H
#define PAXENGINE3_SHADEDNODE_H

#include <memory>
#include <core/rendering/resource/Shader.h>

namespace PAX {
    class Shaded {
    public:
        virtual void registerFlags(Shader::Flags &flags) = 0;
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader) = 0;
    };
}

#endif //PAXENGINE3_SHADEDNODE_H
