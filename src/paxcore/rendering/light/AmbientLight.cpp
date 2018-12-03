//
// Created by paul on 08.11.18.
//

#include <paxcore/rendering/light/AmbientLight.h>

namespace PAX {
    AmbientLight::AmbientLight(const glm::vec3 &color) {
        setColor(color);
    }

    void AmbientLight::uploadTo(const std::shared_ptr<PAX::Shader> &shader) {
        shader->setUniform("lights.ambient.color", this->getColor());
    }
    
    void AmbientLight::setColor(const glm::vec3 &color) {
        this->color = color;
    }
    
    const glm::vec3& AmbientLight::getColor() const {
        return color;
    }
}