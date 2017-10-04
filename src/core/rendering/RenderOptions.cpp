//
// Created by Paul on 30.06.2017.
//

#include <cassert>
#include "../../../include/core/rendering/RenderOptions.h"

namespace PAX {
    bool ShaderOptions::useShader(void *caller, Shader *shader, ShaderPriority priority) {
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

    void ShaderOptions::unuseShader(void *caller) {
        assert(caller == _shaders.top()._owner);

        _shaders.top()._shader->unbind();
        _shaders.pop();
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

    /*
    PAX::Shader *PAX::RenderOptions::getShader() const {
        return _shader;
    }

    void PAX::RenderOptions::setShader(PAX::Shader *shader) {
        RenderOptions::_shader = shader;
    }*/

    ShaderOptions& PAX::RenderOptions::getShaderOptions() {
        return _shaderOptions;
    }
}