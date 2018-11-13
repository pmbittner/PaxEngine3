//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/DirectionalLight.h>

namespace PAX {
    DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec4 &color) : Super(color) {
        setDirection(direction);
    }

    DirectionalLight::~DirectionalLight() {}

    void DirectionalLight::uploadTo(const std::shared_ptr<PAX::Shader> &shader, int index) {
        std::string uniformPrefix = "lights.directionals[" + std::to_string(index) + "]";
        shader->setUniform(uniformPrefix + ".color", this->getColor());
        shader->setUniform(uniformPrefix + ".direction", this->_direction);
    }

    void DirectionalLight::setDirection(const glm::vec3 &direction) {
        _direction = direction;
    }

    const glm::vec3& DirectionalLight::getDirection() const {
        return _direction;
    }
}