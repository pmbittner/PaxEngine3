//
// Created by Paul on 30.06.2017.
//

#include <cassert>
#include <paxutil/math/Transformation.h>
#include <paxcore/rendering/RenderOptions.h>
#include <paxcore/rendering/Renderer.h>

namespace PAX {
    bool ShaderOptions::pushShader(void *caller, Shader* shader, ShaderPriority priority) {
        PAX_assertNotNull(shader, "Shader can't be null!");

        if (_shaders.empty() || _shaders.top()._priority == ShaderPriority::MUTABLE) {
            ShaderUsage usage;
            usage._priority = priority;
            usage._owner = caller;
            usage._shader = shader;
            _shaders.push(usage);

            shader->bind();

            return true;
        }

        return false;
    }

    bool ShaderOptions::popShader(void *caller) {
        if(caller == _shaders.top()._owner) {
            _shaders.top()._shader->unbind();
            _shaders.pop();

            if (!_shaders.empty())
                _shaders.top()._shader->bind();
        }

        return true;
    }

    Shader* ShaderOptions::getShader() {
        if (_shaders.empty())
            return nullptr;
        return _shaders.top()._shader;
    }

    RenderOptions::RenderOptions(const Renderer& renderer) : _renderer(renderer), _camera(nullptr), _worldLayer(nullptr) {
    }

    PAX::Camera *PAX::RenderOptions::getCamera() const {
        return _camera;
    }

    void PAX::RenderOptions::setCamera(PAX::Camera *camera) {
        RenderOptions::_camera = camera;
    }
    
    WorldLayer* RenderOptions::getWorldLayer() const {
        return _worldLayer;
    }
    
    void RenderOptions::setWorldLayer(PAX::WorldLayer *worldLayer) {
        _worldLayer = worldLayer;
    }

    glm::mat4 & PAX::RenderOptions::getTransformationMatrix() {
        return _currentTransform;
    }

    void PAX::RenderOptions::setTransformationMatrix(const glm::mat4 &transform) {
        _currentTransform = transform;
        _renderer.OnTransformationChanged(*this);
    }

    glm::mat4& RenderOptions::getProjectionMatrix() {
        return _currentProjection;
    }

    void RenderOptions::setProjectionMatrix(const glm::mat4 &projection) {
        _currentProjection = projection;
    }

    glm::mat4& RenderOptions::getViewMatrix() {
        return _currentView;
    }

    void RenderOptions::setViewMatrix(const glm::mat4 &view) {
        _currentView = view;
    }

    ShaderOptions& PAX::RenderOptions::getShaderOptions() {
        return _shaderOptions;
    }
}