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

        /// BEGIN FIELDS
        glm::vec2 offset = glm::vec2(0);
        float radius = 1;
        /// END FIELDS

        SphereGravityField();

    public:
        SphereGravityField(
                const std::shared_ptr<Shape2D> & shape,
                float intensity,
                float radius,
                const glm::vec2 & offset = glm::vec2(0));

        /**
         * Creates a SphereGravityField with circular shape.
         * @param intensity
         * @param radius
         */
        SphereGravityField(
                float intensity,
                float radius,
                const glm::vec2 & offset = glm::vec2(0));

        PAX_NODISCARD ClassMetadata getMetadata() override;
        PAX_NODISCARD glm::vec2 getFallingDirection(const glm::vec2 & point) const override;

        void setRadius(float radius);
        PAX_NODISCARD float getRadius() const;
    };
}

#endif //PAXENGINE3_SPHEREGRAVITYFIELD_H
