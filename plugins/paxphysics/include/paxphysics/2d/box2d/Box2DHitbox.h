//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_BOX2DHITBOX_H
#define PAXENGINE3_BOX2DHITBOX_H

#include <paxphysics/2d/Hitbox2D.h>
#include "Box2DWorld.h"

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace PAX::Physics {
    class Box2DHitbox : public Hitbox2D {
        PAX_PROPERTY(PAX::Physics::Box2DHitbox, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Physics::Hitbox2D)
        PAX_PROPERTY_IS_SINGLE

        b2Body * body = nullptr;
        std::vector<b2Fixture *> fixtures;

        void uploadToBox2D(Box2DWorld & box2DWorld);

    public:
        explicit Box2DHitbox();
        ~Box2DHitbox() override;

        void activated() override;
        void deactivated() override;

        void synchronizeBox2D(float metersPerPixel);
        void synchronizePaxEngine(float pixelsPerMeter);

        void setFixedRotation(bool fixedRotation) override;
    };
}

#endif //PAXENGINE3_BOX2DHITBOX_H
