//
// Created by Paul on 30.06.2017.
//

#include "../../../include/core/rendering/RenderOptions.h"

namespace PAX {
    RenderOptions::RenderOptions() {
        _camera = nullptr;
        _shader = nullptr;
    }

    PAX::Camera *PAX::RenderOptions::getCamera() const {
        return _camera;
    }

    void PAX::RenderOptions::setCamera(PAX::Camera *camera) {
        RenderOptions::_camera = camera;
    }

    PAX::Shader *PAX::RenderOptions::getShader() const {
        return _shader;
    }

    void PAX::RenderOptions::setShader(PAX::Shader *shader) {
        RenderOptions::_shader = shader;
    }
}