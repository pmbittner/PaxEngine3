//
// Created by paul on 13.11.18.
//

#include <paxcore/rendering/light/PointLight.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::PointLight, PAX_PROPERTY_IS_CONCRETE)

    PointLight * PointLight::createFromProvider(PAX::ContentProvider & provider) {
        if (auto color = provider.get<glm::vec4>("color")) {
            return new PointLight(color.value());
        } else {
            return new PointLight();
        }
    }

    void PointLight::initializeFromProvider(PAX::ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    void PointLight::uploadTo(PAX::Shader * shader, int index) {

    }
}