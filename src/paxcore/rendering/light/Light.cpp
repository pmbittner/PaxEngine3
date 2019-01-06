//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/Light.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Light)

    Light::Light(const glm::vec4 &color) {
        setColor(color);
    }

    Light::~Light() {}

    const glm::vec4& Light::getColor() const {
        return _color;
    }

    void Light::setColor(const glm::vec4 &color) {
        _color = color;
    }
}