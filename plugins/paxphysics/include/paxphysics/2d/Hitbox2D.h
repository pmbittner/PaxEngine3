//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX2D_H
#define PAXENGINE3_HITBOX2D_H

#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include "Fixture2D.h"

namespace PAX::Physics {
    class Hitbox2D : public GameEntityProperty {
        PAX_PROPERTY(PAX::Physics::Hitbox2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(PAX::GameEntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

        // TODO: Inline fixture here?
        Fixture2D fixture;
        GameEntity* visualizer = nullptr;

        // TODO: Implement
        bool isSensor;

    public:
        static constexpr int HitboxVisualizationZ = 100;

        ~Hitbox2D() override = 0;

        PAX_NODISCARD ClassMetadata getMetadata() override;

        virtual void setFixture(const Fixture2D & fixture);
        PAX_NODISCARD const Fixture2D & getFixture() const;

        void show();
        void hide();
    };
}

#endif //PAXENGINE3_HITBOX2D_H
