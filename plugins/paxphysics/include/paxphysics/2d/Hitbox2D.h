//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX2D_H
#define PAXENGINE3_HITBOX2D_H

#include <paxcore/entity/EntityProperty.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include "Fixture2D.h"

namespace PAX::Physics {
    class Hitbox2D : public EntityProperty {
        PAX_PROPERTY(PAX::Physics::Hitbox2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(PAX::EntityProperty)
        PAX_PROPERTY_IS_SINGLE

    private:
        bool fixedRotation = false;
        std::vector<Fixture2D> fixtures;

    public:
        Hitbox2D();
        ~Hitbox2D() override = 0;

        virtual void setFixtures(const std::vector<Fixture2D> & fixtures);
        [[nodiscard]] const std::vector<Fixture2D> & getFixtures() const;

        virtual void setFixedRotation(bool fixedRotation);
        [[nodiscard]] bool hasFixedRotation() const;
    };
}

#endif //PAXENGINE3_HITBOX2D_H
