//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_SHADERFLAGSCONFIGURATOR_H
#define PAXENGINE3_SHADERFLAGSCONFIGURATOR_H

#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class ShaderFlagsConfigurator {
    public:
        virtual void registerFlags(Shader::Flags &flags) = 0;
    };
}

#endif //PAXENGINE3_SHADERFLAGSCONFIGURATOR_H
