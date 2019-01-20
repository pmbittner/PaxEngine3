//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_DIRECTIONALLIGHT_H
#define PAXENGINE3_DIRECTIONALLIGHT_H

#include "Light.h"

namespace PAX {
    class DirectionalLight : public Light {
        PAX_PROPERTY(DirectionalLight, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Light)
        PAX_PROPERTY_IS_SINGLE

        glm::vec3 _direction;

    public:
        DirectionalLight(const glm::vec3 & direction, const glm::vec4 & color = glm::vec4(1));
        virtual ~DirectionalLight();

        virtual void uploadTo(Shader * shader, int index) override;

        virtual void setDirection(const glm::vec3 & direction);
        const glm::vec3 & getDirection() const;
    };
}

#endif //PAXENGINE3_DIRECTIONALLIGHT_H
