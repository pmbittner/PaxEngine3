//
// Created by Paul on 28.07.2019.
//

#ifndef PAXENGINE3_BOX2DHITBOX_H
#define PAXENGINE3_BOX2DHITBOX_H

#include <paxphysics/2d/Hitbox2D.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace PAX::Physics {
    class Box2DHitbox : public Hitbox2D {
        PAX_PROPERTY(PAX::Physics::Box2DHitbox, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Physics::Hitbox2D)
        PAX_PROPERTY_IS_MULTIPLE

        explicit Box2DHitbox();

    public:
        /**
         *
         * @param shape takes ownership
         * @param material
         */
        Box2DHitbox(Shape2D * shape, const std::shared_ptr<PhysicsMaterial> &material);
        ~Box2DHitbox() override;
    };
}

#endif //PAXENGINE3_BOX2DHITBOX_H
