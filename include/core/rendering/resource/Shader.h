//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SHADER_H
#define PAXENGINE3_SHADER_H

namespace PAX {
    class Shader {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };
}

#endif //PAXENGINE3_SHADER_H
