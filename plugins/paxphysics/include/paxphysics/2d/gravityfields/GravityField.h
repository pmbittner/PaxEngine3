//
// Created by Paul Bittner on 23.01.2021.
//

#ifndef PAXENGINE3_GRAVITYFIELD_H
#define PAXENGINE3_GRAVITYFIELD_H

#include "paxcore/gameentity/GameEntityProperty.h"

namespace PAX::Physics {
    class GravityField : public GameEntityProperty {
        PAX_PROPERTY(GravityField, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        float intensity;

    protected:
        explicit GravityField(float intensity);

    public:
        PAX_NODISCARD virtual bool isInside(const glm::vec2 & point) const = 0;
        PAX_NODISCARD virtual glm::vec2 getFallingDirection(const glm::vec2 & point) const = 0;

        void setIntensity(float intensity);
        PAX_NODISCARD float getIntensity() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_GRAVITYFIELD_H
