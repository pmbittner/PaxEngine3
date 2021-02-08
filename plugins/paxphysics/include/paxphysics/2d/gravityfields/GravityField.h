//
// Created by Paul Bittner on 23.01.2021.
//

#ifndef PAXENGINE3_GRAVITYFIELD_H
#define PAXENGINE3_GRAVITYFIELD_H

#include <paxphysics/2d/Hitbox2D.h>
#include "paxphysics/2d/shape/Shape2D.h"
#include "paxcore/gameentity/GameEntityProperty.h"

namespace PAX::Physics {
    class GravityField : public GameEntityProperty {
        PAX_PROPERTY(GravityField, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        /// BEGIN FIELDS
        std::shared_ptr<Shape2D> shape = nullptr;
        float intensity = 1;
        float priority = 0;
        /// END FIELDS

        Hitbox2D * hitbox = nullptr;
        void initializeHitbox();

    protected:
        GravityField();
        explicit GravityField(const std::shared_ptr<Shape2D> & shape, float intensity);

    public:
        EventHandler<GravityField&, int, int> OnPriorityChanged;

        ~GravityField() override;

        PAX_NODISCARD static const Tag & GetTag();

        PAX_NODISCARD bool isInside(const glm::vec2 & point) const;
        PAX_NODISCARD virtual glm::vec2 getFallingDirection(const glm::vec2 & point) const = 0;

        void setIntensity(float intensity);
        PAX_NODISCARD float getIntensity() const;
        void setPriority(float priority);
        PAX_NODISCARD float getPriority() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
        void attached(GameEntity & entity) override;
        void detached(GameEntity & entity) override;
    };
}

#endif //PAXENGINE3_GRAVITYFIELD_H
