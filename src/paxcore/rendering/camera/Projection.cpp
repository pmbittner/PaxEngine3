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

    void Projection::setFOV(float fov) {
        _fov = fov;
        _dirty = true;
    }

    float Projection::getFOV() {
        return _fov;
    }

    void Projection::setNearPlane(float nearPlane) {
        _near = nearPlane;
        _dirty = true;
    }

    float Projection::getNearPlane() {
        return _near;
    }

    void Projection::setFarPlane(float farPlane) {
        _far = farPlane;
        _dirty = true;
    }

    float Projection::getFarPlane() {
        return _far;
    }

    const glm::ivec2& Projection::getResolution() {
        return _resolution;
    }

    void Projection::setResolution(const glm::ivec2 &res) {
        if (_resolution != res) {
            _resolution = res;
            _dirty = true;
        }
    }
}