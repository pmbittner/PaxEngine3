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
        PAX_PROPERTY_IS_SINGLE

        bool fixedRotation = false;
        std::vector<Fixture2D> fixtures;
        std::vector<GameEntity*> fixtureVisualizers;

    protected:
        Hitbox2D();

    public:
        static constexpr int HitboxVisualizationZ = 100;

        ~Hitbox2D() override = 0;

        PAX_NODISCARD ClassMetadata getMetadata() override;

        virtual void setFixtures(const std::vector<Fixture2D> & fixtures);
        PAX_NODISCARD const std::vector<Fixture2D> & getFixtures() const;

        virtual void setFixedRotation(bool fixedRotation);
        PAX_NODISCARD bool hasFixedRotation() const;

        void show();
        void hide();
    };
}

#endif //PAXENGINE3_HITBOX2D_H
