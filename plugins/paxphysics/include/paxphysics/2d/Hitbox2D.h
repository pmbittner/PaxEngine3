//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX2D_H
#define PAXENGINE3_HITBOX2D_H

#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include <paxphysics/2d/material/PhysicsMaterial.h>

namespace PAX::Physics {
    class Hitbox2D : public GameEntityProperty {
        PAX_PROPERTY(PAX::Physics::Hitbox2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(PAX::GameEntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

        Shape2D * shape = nullptr;
        std::shared_ptr<PhysicsMaterial> material;
        GameEntity* visualizer = nullptr;

        // TODO: Implement
        bool isSensor = false;

    protected:
        Hitbox2D(Shape2D * shape, const std::shared_ptr<PhysicsMaterial> &material);

    public:
        static constexpr int HitboxVisualizationZ = 100;

        ~Hitbox2D() override = 0;

        PAX_NODISCARD ClassMetadata getMetadata() override;

        void show();
        void hide();

        PAX_NODISCARD const Shape2D & getShape() const;
        PAX_NODISCARD const std::shared_ptr<PhysicsMaterial> & getMaterial() const;
    };
}

#endif //PAXENGINE3_HITBOX2D_H
