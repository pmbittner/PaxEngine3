//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

#include <stack>
#include <memory>

#include <paxutil/math/Transformation.h>
#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    class Camera;
    class Renderer;
    class WorldLayer;

    enum class ShaderPriority {
        MUTABLE,
        IMMUTABLE
    };

    class ShaderOptions {
        struct ShaderUsage {
            Shader* _shader = nullptr;
            ShaderPriority _priority = ShaderPriority::MUTABLE;
            void* _owner = nullptr;
        };

        std::stack<ShaderUsage> _shaders;

    public:
        bool pushShader(void* caller, Shader* shader, ShaderPriority priority = ShaderPriority::MUTABLE);
        bool popShader(void* caller);

        Shader* getShader();
    };

    class RenderOptions {
        const Renderer& _renderer;

        Camera *_camera = nullptr;
        WorldLayer *_worldLayer = nullptr;
        
        ShaderOptions _shaderOptions;
        
        glm::mat4 _currentTransform = glm::mat4(1);
        glm::mat4 _currentView = glm::mat4(1);
        glm::mat4 _currentProjection = glm::mat4(1);

        float dt = 0;
        float actual_dt = 0;

    public:
        explicit RenderOptions(const Renderer& renderer, float dt, float actualDt);

        Camera *getCamera() const;
        void setCamera(Camera *camera);

        WorldLayer *getWorldLayer() const;
        void setWorldLayer(WorldLayer *worldLayer);

        glm::mat4& getTransformationMatrix();
        void setTransformationMatrix(const glm::mat4& transform);

        glm::mat4& getProjectionMatrix();
        void setProjectionMatrix(const glm::mat4& projection);

        glm::mat4& getViewMatrix();
        void setViewMatrix(const glm::mat4& view);

        ShaderOptions& getShaderOptions();

        float getDeltaTime();
        float getActualDeltaTime();
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
