//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/SpotLight.h>
#include <paxutil/math/Angles.h>

namespace PAX {
    SpotLight::SpotLight(const glm::vec3 &direction, float openingAngleInDegrees, const glm::vec4 &color) : Super(color) {
        setDirection(direction);
        setOpeningAngleInDegrees(openingAngleInDegrees);
    }

    SpotLight::~SpotLight() {

    }

    void SpotLight::uploadTo(const std::shared_ptr<PAX::Shader> &shader, int index) {

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