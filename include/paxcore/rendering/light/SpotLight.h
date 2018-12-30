//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_SPOTLIGHT_H
#define PAXENGINE3_SPOTLIGHT_H

#include "Light.h"

namespace PAX {
    // Design Decision: SpotLight is not derived from DirectionalLight because
    //                  they differ in behaviour greatly, although they share
    //                  the direction property.
    class SpotLight : public Light {
    PAX_PROPERTY_DERIVES(Light)
    PAX_PROPERTY_IS_SINGLE

        glm::vec3 _direction;
        float _openingAngleInRadians;

    public:
        SpotLight(const glm::vec3 & direction, float openingAngleInDegrees, const glm::vec4 & color = glm::vec4(1));
        virtual ~SpotLight();

        virtual void uploadTo(const std::shared_ptr<Shader>& shader, int index) override;

        virtual void setDirection(const glm::vec3 & direction);
        const glm::vec3 & getDirection() const;

        virtual void setOpeningAngleInDegrees(float degrees);
        float getOpeningAngleInRadians() const;
        float getOpeningAngleInDegrees() const;
    };
}

#endif //PAXENGINE3_SPOTLIGHT_H
