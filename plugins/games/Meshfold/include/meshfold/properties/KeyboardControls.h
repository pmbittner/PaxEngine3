//
// Created by Paul Bittner on 20.03.2020.
//

#ifndef PAXENGINE3_KEYBOARDCONTROLS_H
#define PAXENGINE3_KEYBOARDCONTROLS_H

#include "PointCloudSprite.h"
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/io/event/KeyPressedEvent.h>

namespace PAX {
    class MeshfoldSystem;

    class KeyboardControls : public GameEntityProperty {
        PAX_PROPERTY(KeyboardControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        PAX_PROPERTY_DEPENDS_ON(PointCloudSprite);

        friend MeshfoldSystem;

        float angularSpeed = 1.6f;
        float speed = 40.f;

        float velocity;
        float angularVelocity;

        float accelerationOnPressed(Key key) const;
        float angularAccelerationOnPressed(Key key) const;

    public:
        void attached(GameEntity & e) override;
        void detached(GameEntity & e) override;

        void onKeyDown(KeyPressedEvent & keyPressedEvent);
        void onKeyReleased(KeyReleasedEvent & keyReleasedEvent);

        ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_KEYBOARDCONTROLS_H
