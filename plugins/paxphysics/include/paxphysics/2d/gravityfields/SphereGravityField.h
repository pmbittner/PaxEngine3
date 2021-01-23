//
// Created by Paul Bittner on 23.01.2021.
//

#ifndef PAXENGINE3_SPHEREGRAVITYFIELD_H
#define PAXENGINE3_SPHEREGRAVITYFIELD_H

#include "GravityField.h"

namespace PAX::Physics {
    class SphereGravityField : public GravityField {
        PAX_PROPERTY(SphereGravityField, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GravityField)
        PAX_PROPERTY_IS_SINGLE

        float radius;

        SphereGravityField();

    public:
        SphereGravityField(float intensity, float radius);

        PAX_NODISCARD bool isInside(const glm::vec2 & point) const override;
        PAX_NODISCARD glm::vec2 getFallingDirection(const glm::vec2 & point) const override;

        void setRadius(float radius);
        PAX_NODISCARD float getRadius() const;
    };
}

#endif //PAXENGINE3_SPHEREGRAVITYFIELD_H
