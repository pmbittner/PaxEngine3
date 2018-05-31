//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_NOCLIPCONTROLS_H
#define PAXENGINE3_NOCLIPCONTROLS_H

#include <core/entity/component/Behaviour.h>
#include <glm/vec3.hpp>
#include <core/io/event/KeyPressedEvent.h>
#include <core/io/event/KeyReleasedEvent.h>
#include <core/io/event/MouseButtonReleasedEvent.h>
#include <core/io/event/MouseButtonPressedEvent.h>
#include <core/io/event/MouseMovedEvent.h>
#include <core/io/Keys.h>

#include <utility/macros/MacroIncludes.h>

namespace PAX {
    class NoClipControls : public Behaviour {

        PAX_ENTITYCOMPONENT_BODY(Behaviour, false)

        glm::vec3 relativeMovement;
        glm::vec3 velocity;

        float theta = 0, phi = 0;
        float lastTheta, lastPhi;

        float speed = 1.f;
        float rotspeed = PAX_PI / 8;

        void updateMovement();
        void updateAxis(Key key, int direction);

        void onKeyPressed(KeyPressedEvent& e);
        void onKeyReleased(KeyReleasedEvent& e);

        void onMouseDragged(MouseMovedEvent& e);
        void onMousePressed(MouseButtonPressedEvent& e);
        void onMouseReleased(MouseButtonReleasedEvent& e);

    public:
        NoClipControls();
        ~NoClipControls();

        virtual void update() override;

        void resetOrientation(float theta = 0.0f, float phi = 0.0f);
    };
}
#endif //PAXENGINE3_NOCLIPCONTROLS_H
