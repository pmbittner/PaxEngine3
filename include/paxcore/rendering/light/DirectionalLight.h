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

        glm::vec3 direction = glm::vec3(1, 0, 0);

    protected:
        DirectionalLight();

    public:
        explicit DirectionalLight(const glm::vec3 & direction, const glm::vec4 & color = glm::vec4(1));
        ~DirectionalLight() override;

        void uploadTo(Shader * shader, int index) override;

        virtual void setDirection(const glm::vec3 & direction);
        PAX_NODISCARD const glm::vec3 & getDirection() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_DIRECTIONALLIGHT_H
