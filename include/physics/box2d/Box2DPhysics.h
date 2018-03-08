//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <physics/Physics.h>
#include <Box2D/Box2D.h>

namespace PAX {
    namespace Box2D {
        class Physics;
    }

    PAX_ENTITYCOMPONENT(Box2D::Physics, PAX::Physics, true)
    namespace Box2D {
        class Physics : public PAX::Physics {
            PAX_ENTITYCOMPONENT_BODY

            b2BodyDef _bodyDef;
            b2FixtureDef _fixtureDef;

            b2Body *_body;
            b2Fixture *_fixture;

        public:
            Physics(const b2BodyDef& bodyDef);

            void createFor(b2World& world);
            virtual void attached(Entity *entity) override;
        };
    }
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
