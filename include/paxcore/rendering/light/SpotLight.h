//
// Created by Paul on 10.09.2018.
//

#ifndef PAXENGINE3_SPOTLIGHT_H
#define PAXENGINE3_SPOTLIGHT_H

#include "Light.h"

namespace PAX {
    // Design Decision: SpotLight is not derived from DirectionalLight because
    //                  they differ in behaviour greatly, although they share
    //                  the direction field.
    class SpotLight : public Light {
        PAX_PROPERTY(SpotLight, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Light)
        PAX_PROPERTY_IS_SINGLE

        glm::vec3 direction = glm::vec3(1, 0, 0);
        float openingAngleInDegrees = 60.f;

    protected:
        SpotLight();

    public:
        SpotLight(const glm::vec3 & direction, float openingAngleInDegrees, const glm::vec4 & color = glm::vec4(1));
        ~SpotLight() override;

        void uploadTo(PAX::Shader * shader, int index) override;

        virtual void setDirection(const glm::vec3 & direction);
        PAX_NODISCARD const glm::vec3 & getDirection() const;

        virtual void setOpeningAngleInDegrees(float degrees);
        PAX_NODISCARD float getOpeningAngleInRadians() const;
        PAX_NODISCARD float getOpeningAngleInDegrees() const;

        ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_SPOTLIGHT_H
