//
// Created by Paul Bittner on 07.02.2021.
//

#ifndef MESHFOLD_DIRECTIONALGRAVITYFIELD_H
#define MESHFOLD_DIRECTIONALGRAVITYFIELD_H

#include "GravityField.h"

namespace PAX::Physics {
    class DirectionalGravityField : public GravityField {
        PAX_PROPERTY(DirectionalGravityField, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GravityField)
        PAX_PROPERTY_IS_SINGLE

        /// BEGIN FIELDS
        glm::vec2 direction = glm::vec2(0, -1);
        /// END FIELDS

        DirectionalGravityField();

    public:
        explicit DirectionalGravityField(
                const std::shared_ptr<Shape2D> & shape,
                float intensity,
                const glm::vec2 & direction);

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
        PAX_NODISCARD glm::vec2 getFallingDirection(const glm::vec2 & point) const override;

        void setDirection(const glm::vec2 & direction);
        PAX_NODISCARD const glm::vec2 & getDirection() const;
    };
}

#endif //MESHFOLD_DIRECTIONALGRAVITYFIELD_H
