//
// Created by paul on 08.11.18.
//

#ifndef PAXENGINE3_AMBIENTLIGHT_H
#define PAXENGINE3_AMBIENTLIGHT_H

#include <paxcore/world/WorldLayerProperty.h>

namespace PAX {
    class AmbientLight : public WorldLayerProperty {
        PAX_PROPERTY(AmbientLight, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldLayerProperty)
        PAX_PROPERTY_IS_SINGLE

        glm::vec3 color;

    public:
        AmbientLight(const glm::vec3 & color = {0.2, 0.2, 0.2});

        virtual void uploadTo(Shader* shader);

        void setColor(const glm::vec3 & color);
        const glm::vec3& getColor() const;
    };
}

#endif //PAXENGINE3_AMBIENTLIGHT_H
