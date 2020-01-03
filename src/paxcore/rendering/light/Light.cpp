//
// Created by Paul on 10.09.2018.
//

#include <paxcore/rendering/light/Light.h>

namespace PAX {
    PAX_PROPERTY_INIT(PAX::Light) {}

    Light::Light(const glm::vec4 &color) : color(color) {

    }

    Light::~Light() = default;

    ClassMetadata Light::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(color));
        return m;
    }

    const glm::vec4& Light::getColor() const {
        return color;
    }

    void Light::setColor(const glm::vec4 &color) {
        this->color = color;
    }
}