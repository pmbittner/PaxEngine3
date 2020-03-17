//
// Created by paul on 08.11.18.
//

#ifndef PAXENGINE3_AMBIENTLIGHT_H
#define PAXENGINE3_AMBIENTLIGHT_H

#include <paxcore/world/WorldProperty.h>

namespace PAX {
    class AmbientLight : public WorldProperty {
        PAX_PROPERTY(AmbientLight, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        glm::vec3 color;

    public:
        explicit AmbientLight(const glm::vec3 & color = {0.2, 0.2, 0.2});

        virtual void uploadTo(Shader* shader);

        void setColor(const glm::vec3 & color);
        PAX_NODISCARD const glm::vec3& getColor() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_AMBIENTLIGHT_H
