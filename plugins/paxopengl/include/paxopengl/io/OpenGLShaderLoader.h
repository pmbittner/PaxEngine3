//
// Created by Paul on 08.10.2017.
//

#ifndef PAXENGINE3_OPENGLSHADERLOADER_H
#define PAXENGINE3_OPENGLSHADERLOADER_H

#include <paxcore/rendering/data/Shader.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLShaderLoader :
                public ResourceLoader<Shader, Shader::FileInfo>,
                public ResourceLoader<Shader, Shader::FileInfo, Shader::Flags> {
        public:
            PAX_NODISCARD std::shared_ptr<Shader> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;

            PAX_NODISCARD bool canLoad(Shader::FileInfo) const override;
            PAX_NODISCARD std::shared_ptr<Shader> load(Shader::FileInfo) override;

            PAX_NODISCARD bool canLoad(Shader::FileInfo, Shader::Flags flags) const override;
            PAX_NODISCARD std::shared_ptr<Shader> load(Shader::FileInfo, Shader::Flags flags) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADERLOADER_H
