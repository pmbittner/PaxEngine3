//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

#include <core/rendering/resource/Shader.h>
#include <stack>
#include <utility/MacroIncludes.h>

namespace PAX {
    class Camera;

    enum class ShaderPriority {
        MUTABLE,
        IMMUTABLE
    };

    class ShaderOptions {
        struct ShaderUsage {
            Shader *_shader;
            ShaderPriority _priority = ShaderPriority::MUTABLE;
            void* _owner;
        };

        std::stack<ShaderUsage> _shaders;

    public:
        bool useShader(void* caller, Shader *shader, ShaderPriority priority = ShaderPriority::MUTABLE);
        void unuseShader(void* caller);
    };

    class RenderOptions {
        Camera *_camera = nullptr;
        ShaderOptions _shaderOptions;

    public:
        RenderOptions();

        Camera *getCamera() const;
        void setCamera(Camera *camera);

        ShaderOptions& getShaderOptions();
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
