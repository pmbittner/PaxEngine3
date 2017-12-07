//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

#include <stack>
#include <core/entity/Transform.h>
#include <core/rendering/resource/Shader.h>
#include <utility/macros/MacroIncludes.h>

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

        void activateShader(ShaderUsage & usage);
        void deactivateCurrentShader();

    public:
        bool useShader(void* caller, Shader *shader, ShaderPriority priority = ShaderPriority::MUTABLE);
        void unuseShader(void* caller);

        Shader* getShader();
    };

    class RenderOptions {
        Camera *_camera = nullptr;
        ShaderOptions _shaderOptions;
        Transform* _currentTransform;

    public:
        RenderOptions();

        Camera *getCamera() const;
        void setCamera(Camera *camera);

        Transform& getTransformation() const;
        void setTransformation(Transform& transform);


        ShaderOptions& getShaderOptions();
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
