//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/DirectionalLight.h>

namespace PAX {
    DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec4 &color) : Super(color) {
        setDirection(direction);
    }

    DirectionalLight::~DirectionalLight() {}

    void DirectionalLight::setDirection(const glm::vec3 &direction) {
        _direction = direction;
    }

    const glm::vec3& DirectionalLight::getDirection() const {
        return _direction;
    }
}