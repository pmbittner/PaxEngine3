//
// Created by paul on 08.11.18.
//

#include <paxcore/rendering/light/AmbientLight.h>

namespace PAX {
    PAX_PROPERTY_INIT(PAX::AmbientLight) {}

    ClassMetadata AmbientLight::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(color));
        return m;
    }

    AmbientLight::AmbientLight(const glm::vec3 &color) : color(color) {

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