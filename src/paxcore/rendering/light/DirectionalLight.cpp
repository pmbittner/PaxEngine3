//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/DirectionalLight.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::DirectionalLight)

    ClassMetadata DirectionalLight::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(direction)).flags |= Field::IsMandatory;
        return m;
    }

    DirectionalLight::DirectionalLight() = default;

    DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec4 &color) : Super(color), direction(direction) {

    }

    DirectionalLight::~DirectionalLight() = default;

    void DirectionalLight::uploadTo(PAX::Shader* shader, int index) {
        std::string uniformPrefix = "lights.directionals[" + std::to_string(index) + "]";
        shader->setUniform(uniformPrefix + ".color", this->getColor());
        shader->setUniform(uniformPrefix + ".direction", this->direction);
    }

    void DirectionalLight::setDirection(const glm::vec3 &direction) {
        this->direction = direction;
    }

    const glm::vec3 & DirectionalLight::getDirection() const {
        return this->direction;
    }
}