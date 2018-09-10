//
// Created by Paul on 09.12.2017.
//

#include <paxcore/entity/component/behaviours/NoClipControls.h>

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/Transform.h>
#include <paxcore/service/Services.h>

#include <paxutil/lib/GlmIncludes.h>

#include <paxutil/macros/MacroIncludes.h>
#include <paxcore/time/Time.h>

namespace PAX {
    NoClipControls::NoClipControls() {
        EventService& e = Services::GetEventService();
        e.add<KeyPressedEvent, NoClipControls, &NoClipControls::onKeyPressed>(this);
        e.add<KeyReleasedEvent, NoClipControls, &NoClipControls::onKeyReleased>(this);
        e.add<MouseButtonPressedEvent, NoClipControls, &NoClipControls::onMousePressed>(this);
        e.add<MouseButtonReleasedEvent, NoClipControls, &NoClipControls::onMouseReleased>(this);
    }

    NoClipControls::~NoClipControls() {
        EventService& e = Services::GetEventService();
        e.remove<KeyPressedEvent, NoClipControls, &NoClipControls::onKeyPressed>(this);
        e.remove<KeyReleasedEvent, NoClipControls, &NoClipControls::onKeyReleased>(this);
        e.remove<MouseButtonPressedEvent, NoClipControls, &NoClipControls::onMousePressed>(this);
        e.remove<MouseButtonReleasedEvent, NoClipControls, &NoClipControls::onMouseReleased>(this);
    }

    void NoClipControls::updateMovement() {
        glm::vec3 lookDir(sin(theta) * cos(phi), sin(phi), cos(theta) * cos(phi));
        glm::vec3 upDir (sin(theta)* sin(phi)*-1,cos(phi),cos(theta)*sin(phi)*-1);

        glm::vec3 verticalVelocity = glm::vec3(0, relativeMovement.y, 0);
        glm::vec3 forwardVelocity = lookDir * relativeMovement.z;
        glm::vec3 sidewardVelocity = glm::cross(upDir, lookDir) * relativeMovement.x;

        velocity = Time::DeltaF * speed * glm::normalize(forwardVelocity + sidewardVelocity + verticalVelocity);
    }

    void NoClipControls::update() {
        if (glm::length2(velocity) > 0) {
            getOwner()->getTransform().position() += velocity;
        }
    }

    void NoClipControls::updateAxis(Key key, int direction) {
        switch (key) {
            case Key::W: {
                relativeMovement.z -= direction;
                break;
            }
            case Key::S: {
                relativeMovement.z += direction;
                break;
            }
            case Key::D: {
                relativeMovement.x += direction;
                break;
            }
            case Key::A: {
                relativeMovement.x -= direction;
                break;
            }
            case Key::R: {
                relativeMovement.y += direction;
                break;
            }
            case Key::F: {
                relativeMovement.y -= direction;
                break;
            }
            default: break; //other keys are okay but we do not use them
        }

        updateMovement();
    }

    void NoClipControls::onMousePressed(MouseButtonPressedEvent &e) {
        if (e.button == MouseButton::RIGHT) {
            lastPhi = phi;
            lastTheta = theta;
            Services::GetEventService().add<MouseMovedEvent, NoClipControls, &NoClipControls::onMouseDragged>(this);
        }
    }

    void NoClipControls::onMouseReleased(MouseButtonReleasedEvent &e) {
        if (e.button == MouseButton::RIGHT) {
            Services::GetEventService().remove<MouseMovedEvent, NoClipControls, &NoClipControls::onMouseDragged>(this);
        }
    }

    void NoClipControls::onMouseDragged(MouseMovedEvent &e) {
        Transform& t = getOwner()->getTransform();

        float dt = Time::DeltaF * rotspeed;
        float dx = e.oldX - e.mouse->getX();
        float dy = e.oldY - e.mouse->getY();

        theta = theta + dx * dt;
        //lastTheta = theta;
        phi = phi + dy * dt;
        phi = static_cast<float>(
                (std::max)(
                        (std::min)(
                                PAX_HALF_PI,
                                static_cast<double>(phi)
                        ),
                        -PAX_HALF_PI
                )
        );

        t.rotation().y = theta;
        t.rotation().x = phi;

        updateMovement();
    }

    void NoClipControls::onKeyPressed(KeyPressedEvent &e) {
        if (!e.repeated)
            updateAxis(e.button, 1);
    }

    void NoClipControls::onKeyReleased(KeyReleasedEvent &e) {
        updateAxis(e.button, -1);
    }
}