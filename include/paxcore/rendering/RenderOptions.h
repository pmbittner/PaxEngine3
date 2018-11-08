//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_RENDEROPTIONS_H
#define PAXENGINE3_RENDEROPTIONS_H

#include <stack>
#include <memory>

#include <paxutil/math/Transformation.h>
#include <paxcore/rendering/data/Shader.h>
#include <paxutil/macros/MacroIncludes.h>

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
            std::shared_ptr<Shader> _shader = nullptr;
            ShaderPriority _priority = ShaderPriority::MUTABLE;
            void* _owner = nullptr;
        };

        std::stack<ShaderUsage> _shaders;

    public:
        bool pushShader(void* caller, const std::shared_ptr<Shader>& shader, ShaderPriority priority = ShaderPriority::MUTABLE);
        bool popShader(void* caller);

        const std::shared_ptr<Shader>& getShader();
    };

    class RenderOptions {
        const Renderer& _renderer;

        Camera *_camera = nullptr;
        WorldLayer *_worldLayer = nullptr;
        
        ShaderOptions _shaderOptions;
        
        glm::mat4 _currentTransform;
        glm::mat4 _currentView;
        glm::mat4 _currentProjection;

    public:
        RenderOptions(const Renderer& renderer);

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
    };
}

#endif //PAXENGINE3_RENDEROPTIONS_H
