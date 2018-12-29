//
// Created by Paul on 08.10.2017.
//

#ifndef PAXENGINE3_OPENGLSHADERLOADER_H
#define PAXENGINE3_OPENGLSHADERLOADER_H

#include <paxcore/rendering/data/Shader.h>
#include <paxcore/io/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLShaderLoader : public ResourceLoader<Shader, Shader::FileInfo>, public ResourceLoader<Shader, Shader::FileInfo, Shader::Flags> {
        public:
            virtual bool canLoad(Shader::FileInfo) override;
            virtual std::shared_ptr<Shader> load(Shader::FileInfo) override;

            virtual bool canLoad(Shader::FileInfo, Shader::Flags flags) override;
            virtual std::shared_ptr<Shader> load(Shader::FileInfo, Shader::Flags flags) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADERLOADER_H
