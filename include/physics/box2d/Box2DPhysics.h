//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICS_H
#define PAXENGINE3_BOX2DPHYSICS_H

#include <physics/Physics.h>
#include <core/entity/EntityComponent.h>

namespace PAX {
    namespace Box2D {
        class Physics;
    }

    PAX_ENTITYCOMPONENT(Box2D::Physics, PAX::Physics, true)
    namespace Box2D {
        
        class Physics : public PAX::Physics {
            PAX_ENTITYCOMPONENT_BODY

        public:
            Physics();
        };
    }
}

#endif //PAXENGINE3_BOX2DPHYSICS_H
