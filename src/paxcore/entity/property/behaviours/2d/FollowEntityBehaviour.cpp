//
// Created by paul on 07.01.19.
//

#include "paxcore/entity/property/behaviours/2d/FollowEntityBehaviour.h"
#include <paxcore/time/Time.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::FollowEntityBehaviour, PAX_PROPERTY_IS_CONCRETE)

    FollowEntityBehaviour * FollowEntityBehaviour::createFromProvider(ContentProvider & provider) {
        // FIXME:
        return new FollowEntityBehaviour(nullptr);//provider.require<Entity*>("target"));
    }

    void FollowEntityBehaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    void FollowEntityBehaviour::update() {
        if (target) {
            Transformation &me = getOwner()->getTransformation();
            Transformation &he = target->getTransformation();
            me.position2D() = me.position2D() + (he.position2D() - me.position2D()) * speed * Time::DeltaF;
        }
    }
}