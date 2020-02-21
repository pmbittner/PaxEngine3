//
// Created by Paul on 30.06.2017.
//

#include <paxcore/rendering/camera/Projection.h>

namespace PAX {
    const glm::mat4& Projection::toMatrix() {
        if (_dirty) {
            calcMatrix();
            _dirty = false;
        }

        return _matrix;
    }

    void Projection::calcMatrix() {
        _matrix = glm::mat4(1);
    }

    const glm::ivec2& Projection::getResolution() const {
        return _resolution;
    }

    void Projection::setResolution(const glm::ivec2 &res) {
        if (_resolution != res) {
            _resolution = res;
            _dirty = true;
        }
    }
    
    void Projection::makeDirty() {
        _dirty = true;
    }
}