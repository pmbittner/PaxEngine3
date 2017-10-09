//
// Created by Paul on 08.10.2017.
//

#ifndef PAXENGINE3_OPENGLSHADERLOADER_H
#define PAXENGINE3_OPENGLSHADERLOADER_H

#include <core/rendering/resource/Shader.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLShaderLoader : public ResourceLoader<Shader, const char*, const char*> {
        public:
            virtual bool canLoad(const char* vertexShaderPath, const char* fragmentShaderPath) override;
            virtual Shader *load(const char* vertexShaderPath, const char* fragmentShaderPath) override;
            virtual bool free(Shader *res) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADERLOADER_H
