//
// Created by Paul on 30.06.2017.
//

#include <cassert>
#include <core/entity/Transform.h>
#include "../../../include/core/rendering/RenderOptions.h"

namespace PAX {
    void ShaderOptions::activateShader(ShaderUsage &usage) {
        usage._shader->bind();
    }

    void ShaderOptions::deactivateCurrentShader() {
        _shaders.top()._shader->unbind();
        _shaders.pop();

        if (!_shaders.empty())
            activateShader(_shaders.top());
    }

    bool ShaderOptions::useShader(void *caller, Shader *shader, ShaderPriority priority) {
        PAX_assertNotNull(shader, "Shader can't be null!");

        if (_shaders.empty() || _shaders.top()._priority == ShaderPriority::MUTABLE) {
            ShaderUsage usage;
            usage._priority = priority;
            usage._owner = caller;
            usage._shader = shader;
            _shaders.push(usage);

            activateShader(usage);

            return true;
        }

        return false;
    }

    void ShaderOptions::unuseShader(void *caller) {
        assert(caller == _shaders.top()._owner);
        deactivateCurrentShader();
    }

    Shader *ShaderOptions::getShader() {
        if (_shaders.empty())
            return nullptr;
        return _shaders.top()._shader;
    }

    RenderOptions::RenderOptions() {
        _camera = nullptr;
    }

    PAX::Camera *PAX::RenderOptions::getCamera() const {
        return _camera;
    }

    void PAX::RenderOptions::setCamera(PAX::Camera *camera) {
        RenderOptions::_camera = camera;
    }

    glm::mat4 & PAX::RenderOptions::getTransformation() {
        return _currentTransform;
    }

    void PAX::RenderOptions::setTransformation(const glm::mat4 &transform) {
        _currentTransform = transform;
    }

    ShaderOptions& PAX::RenderOptions::getShaderOptions() {
        return _shaderOptions;
    }
}