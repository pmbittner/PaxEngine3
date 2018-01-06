//
// Created by Paul on 08.10.2017.
//

#ifndef PAXENGINE3_OPENGLSHADERLOADER_H
#define PAXENGINE3_OPENGLSHADERLOADER_H

#include <core/rendering/resource/Shader.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLShaderLoader : public ResourceLoader<Shader, Path, Path> {
        public:
            virtual bool canLoad(Path vertexShaderPath, Path fragmentShaderPath) override;
            virtual Shader *load(Path vertexShaderPath, Path fragmentShaderPath) override;
            virtual bool free(Shader *res) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADERLOADER_H
