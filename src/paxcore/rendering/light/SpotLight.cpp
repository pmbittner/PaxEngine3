//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/SpotLight.h>
#include <paxutil/math/Angles.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::SpotLight, PAX_PROPERTY_IS_CONCRETE)

    SpotLight * SpotLight::createFromProvider(PAX::ContentProvider & provider) {
        auto direction = provider.require<glm::vec3>("direction");
        auto openingAngle = provider.require<float>("openingAngle");

        if (auto color = provider.get<glm::vec4>("color")) {
            return new SpotLight(direction, openingAngle, color.value());
        } else {
            return new SpotLight(direction, openingAngle);
        }
    }

    void SpotLight::initializeFromProvider(PAX::ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    SpotLight::SpotLight(const glm::vec3 &direction, float openingAngleInDegrees, const glm::vec4 &color) : Super(color) {
        setDirection(direction);
        setOpeningAngleInDegrees(openingAngleInDegrees);
    }

    SpotLight::~SpotLight() {

    }

    void SpotLight::uploadTo(PAX::Shader * shader, int index) {

    }

    void SpotLight::setDirection(const glm::vec3 &direction) {
        _direction = direction;
    }

    const glm::vec3& SpotLight::getDirection() const {
        return _direction;
    }

    void SpotLight::setOpeningAngleInDegrees(float degrees) {
        _openingAngleInRadians = PAX::Math::toRadians(degrees);
    }

    float SpotLight::getOpeningAngleInRadians() const {
        return _openingAngleInRadians;
    }

    float SpotLight::getOpeningAngleInDegrees() const {
        return PAX::Math::toDegrees(_openingAngleInRadians);
    }
}