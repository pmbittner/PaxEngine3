//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

#include <stack>
#include <core/entity/Transform.h>
#include <core/rendering/data/Shader.h>
#include <utility/macros/MacroIncludes.h>
#include <memory>

namespace PAX {
    class Camera;

    enum class ShaderPriority {
        MUTABLE,
        IMMUTABLE
    };

    class ShaderOptions {
        struct ShaderUsage {
            std::shared_ptr<Shader> _shader = nullptr;
            ShaderPriority _priority = ShaderPriority::MUTABLE;
            void* _owner = nullptr;
        };

        std::stack<ShaderUsage> _shaders;

        void activateShader(ShaderUsage & usage);
        void deactivateCurrentShader();

    public:
        bool useShader(void* caller, const std::shared_ptr<Shader>& shader, ShaderPriority priority = ShaderPriority::MUTABLE);
        void unuseShader(void* caller);

        const std::shared_ptr<Shader>& getShader();
    };

    class RenderOptions {
        Camera *_camera = nullptr;
        ShaderOptions _shaderOptions;
        glm::mat4 _currentTransform;

    public:
        RenderOptions();

        Camera *getCamera() const;
        void setCamera(Camera *camera);

        glm::mat4& getTransformation();
        void setTransformation(const glm::mat4& transform);

        ShaderOptions& getShaderOptions();
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
