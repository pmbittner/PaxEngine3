//
// Created by paul on 13.11.18.
//

#include <paxcore/rendering/light/PointLight.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::PointLight)

    PointLight::PointLight(const glm::vec4 &color) : Super(color) {}
    PointLight::~PointLight() = default;

    void PointLight::uploadTo(PAX::Shader * shader, int index) {
        PAX_NOT_IMPLEMENTED();
    }
}