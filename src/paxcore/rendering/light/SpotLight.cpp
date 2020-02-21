//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/SpotLight.h>
#include <paxutil/math/Angles.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::SpotLight)

    ClassMetadata SpotLight::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(direction)).flags = Field::IsMandatory;
        m.add(paxfieldof(openingAngleInDegrees)).flags = Field::IsMandatory;
        return m;
    }

    SpotLight::SpotLight() = default;

    SpotLight::SpotLight(const glm::vec3 &direction, float openingAngleInDegrees, const glm::vec4 &color)
    : Super(color), direction(direction), openingAngleInDegrees(openingAngleInDegrees) {

    }

    SpotLight::~SpotLight() = default;

    void SpotLight::uploadTo(PAX::Shader * shader, int index) {
        PAX_NOT_IMPLEMENTED();
    }

    void SpotLight::setDirection(const glm::vec3 & direction) {
        this->direction = direction;
    }

    const glm::vec3& SpotLight::getDirection() const {
        return direction;
    }

    void SpotLight::setOpeningAngleInDegrees(float degrees) {
        openingAngleInDegrees = degrees;
    }

    float SpotLight::getOpeningAngleInRadians() const {
        return PAX::Math::toRadians(openingAngleInDegrees);;
    }

    float SpotLight::getOpeningAngleInDegrees() const {
        return openingAngleInDegrees;
    }
}