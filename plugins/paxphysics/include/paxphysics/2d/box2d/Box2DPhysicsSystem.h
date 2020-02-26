//
// Created by Paul on 21.01.2018.
//

#ifndef PAXENGINE3_BOX2DPHYSICSSYSTEM_H
#define PAXENGINE3_BOX2DPHYSICSSYSTEM_H

#include "Box2DHitbox.h"
#include "polypropylene/system/PropertyPool.h"

namespace PAX::Physics {
    class Box2DPhysicsSystem : public PropertyOwningSystem<PAX::Physics::Box2DHitbox> {
        using Super = PropertyOwningSystem<PAX::Physics::Box2DHitbox>;

        float pixelsPerMeter = 1;
        float metersPerPixel = 1;

    public:
        explicit Box2DPhysicsSystem(float pixelsPerMeter);

        void initialize(Game *game) override;
        void update(UpdateOptions & options) override;

        void setPixelsPerMeter(float pixelsPerMeter);
        float getMetersPerPixel();
        float getPixelsPerMeter();
    };
}

#endif //PAXENGINE3_BOX2DPHYSICSSYSTEM_H
