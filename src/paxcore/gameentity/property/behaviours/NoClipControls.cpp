//
// Created by Paul on 09.12.2017.
//

#include <paxcore/gameentity/property/behaviours/NoClipControls.h>
#include <paxcore/gameentity/GameEntity.h>
#include <paxutil/math/Transformation.h>
#include <paxcore/service/Services.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::NoClipControls)

    ClassMetadata NoClipControls::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(speed));
        m.add(paxfieldalias("mouseSensivityInRadiansPerPixel", mousesensivity));
        return m;
    }

    NoClipControls::NoClipControls() : velocity(0), relativeMovement(0) {
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
        Transformation & t = getOwner()->getTransformation();
        glm::vec3 lookDir = t.getLookDirection();
        glm::vec3 upDir = t.getUpDirection();

        glm::vec3 verticalVelocity = glm::vec3(0, relativeMovement.y, 0);
        glm::vec3 forwardVelocity = lookDir * -relativeMovement.z;
        glm::vec3 sidewardVelocity = glm::cross(lookDir, upDir) * relativeMovement.x;

        velocity = speed * glm::normalize(forwardVelocity + sidewardVelocity + verticalVelocity);
    }

    void NoClipControls::update(UpdateOptions & options) {
        auto distance = options.dt * velocity;

        if (glm::length2(distance) > 0) {
            getOwner()->getTransformation().position() += distance;
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

            lastMouseX = e.mouse->getScreenPosition().x;
            lastMouseY = e.mouse->getScreenPosition().y;

            Services::GetEventService().add<MouseMovedEvent, NoClipControls, &NoClipControls::onMouseDragged>(this);
        }
    }

    void NoClipControls::onMouseReleased(MouseButtonReleasedEvent &e) {
        if (e.button == MouseButton::RIGHT) {
            Services::GetEventService().remove<MouseMovedEvent, NoClipControls, &NoClipControls::onMouseDragged>(this);
        }
    }

    void NoClipControls::onMouseDragged(MouseMovedEvent &e) {
        Transformation& t = getOwner()->getTransformation();

        int dx = lastMouseX - e.mouse->getScreenPosition().x;
        int dy = lastMouseY - e.mouse->getScreenPosition().y;
        theta = lastTheta - dx * mousesensivity;
        phi   = lastPhi   + dy * mousesensivity;
        phi = static_cast<float>(
                (std::max)(
                        (std::min)(
                                M_PI_2,
                                static_cast<double>(phi)
                        ),
                        -M_PI_2
                )
        );

        t.setRotation(theta, phi);

        updateMovement();
    }

    void NoClipControls::onKeyPressed(KeyPressedEvent &e) {
        if (!e.repeated)
            updateAxis(e.button, 1);
    }

    void NoClipControls::onKeyReleased(KeyReleasedEvent &e) {
        updateAxis(e.button, -1);
    }

    void NoClipControls::setSpeed(float speed) {
        this->speed = speed;
    }

    float NoClipControls::getSpeed() {
        return speed;
    }

    void NoClipControls::setMouseSensivity(float degreesPerPixel) {
        mousesensivity = glm::radians(degreesPerPixel);
    }

    float NoClipControls::getMouseSensivity() {
        return glm::degrees(mousesensivity);
    }
}