//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_POINTLIGHT_H
#define PAXENGINE3_POINTLIGHT_H

#include "Light.h"

namespace PAX {
    class PointLight : public Light {
        PAX_PROPERTY(PointLight)
        PAX_PROPERTY_DERIVES(Light)
        PAX_PROPERTY_IS_SINGLE

    public:
        PointLight(const glm::vec4 & color = glm::vec4(1)) : Super(color) {}
        virtual ~PointLight() {}

        virtual void uploadTo(PAX::Shader * shader, int index) override;
    };
}

#endif //PAXENGINE3_POINTLIGHT_H
