//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_NOCLIPCONTROLS_H
#define PAXENGINE3_NOCLIPCONTROLS_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxutil/math/MathDefines.h>

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseMovedEvent.h>
#include <paxcore/io/Keys.h>

namespace PAX {
    class NoClipControls : public Behaviour {
        PAX_PROPERTY(NoClipControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Behaviour)
        PAX_PROPERTY_IS_SINGLE

        glm::vec3 relativeMovement;
        glm::vec3 velocity;

        float theta = 0, phi = 0;
        float lastTheta = 0, lastPhi = 0;
        int lastMouseX = 0, lastMouseY = 0;

        float speed = 1.f;
        float mousesensivity = float(M_PI / 400.0); // radians per pixel

        void updateMovement();
        void updateAxis(Key key, int direction);

        void onKeyPressed(KeyPressedEvent& e);
        void onKeyReleased(KeyReleasedEvent& e);

        void onMouseDragged(MouseMovedEvent& e);
        void onMousePressed(MouseButtonPressedEvent& e);
        void onMouseReleased(MouseButtonReleasedEvent& e);

    public:
        NoClipControls();
        ~NoClipControls() override;

        void update(UpdateOptions & options) override;

        void setSpeed(float speed);
        float getSpeed();

        void setMouseSensivity(float degreesPerPixel);
        float getMouseSensivity();

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}
#endif //PAXENGINE3_NOCLIPCONTROLS_H
