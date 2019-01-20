//
// Created by paul on 08.11.18.
//

#include <paxcore/rendering/light/AmbientLight.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::AmbientLight, PAX_PROPERTY_IS_CONCRETE)

    AmbientLight * AmbientLight::createFromProvider(PAX::ContentProvider & provider) {
        return new AmbientLight(provider.require<glm::vec3>("color"));
    }

    void AmbientLight::initializeFromProvider(PAX::ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    AmbientLight::AmbientLight(const glm::vec3 &color) {
        setColor(color);
    }

    void AmbientLight::uploadTo(PAX::Shader* shader) {
        shader->setUniform("lights.ambient.color", this->getColor());
    }
    
    void AmbientLight::setColor(const glm::vec3 &color) {
        this->color = color;
    }
    
    const glm::vec3& AmbientLight::getColor() const {
        return color;
    }
}