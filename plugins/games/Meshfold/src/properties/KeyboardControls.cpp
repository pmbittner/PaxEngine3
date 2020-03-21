//
// Created by Paul Bittner on 20.03.2020.
//

#include <meshfold/properties/KeyboardControls.h>
#include <paxcore/service/Services.h>

namespace PAX {
    PAX_PROPERTY_IMPL(KeyboardControls)

    ClassMetadata KeyboardControls::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(speed));
        m.add(paxfieldof(angularSpeed));
        return m;
    }

    void KeyboardControls::attached(PAX::GameEntity &e) {
        Super::attached(e);

        Services::GetEventService().add<KeyPressedEvent, KeyboardControls, &KeyboardControls::onKeyDown>(this);
        Services::GetEventService().add<KeyReleasedEvent, KeyboardControls, &KeyboardControls::onKeyReleased>(this);
    }

    void KeyboardControls::detached(PAX::GameEntity &e) {
        Super::detached(e);

        Services::GetEventService().remove<KeyPressedEvent, KeyboardControls, &KeyboardControls::onKeyDown>(this);
        Services::GetEventService().remove<KeyReleasedEvent, KeyboardControls, &KeyboardControls::onKeyReleased>(this);
    }

    float KeyboardControls::accelerationOnPressed(PAX::Key key) const {
        switch (key) {
            case Key::UP: {
                return speed;
            }
            case Key::DOWN: {
                return -speed;
            }

            default: break;
        }
        return {};
    }

    float KeyboardControls::angularAccelerationOnPressed(PAX::Key key) const {
        switch (key) {
            case Key::LEFT: {
                return angularSpeed;
            }
            case Key::RIGHT: {
                return -angularSpeed;
            }

            default: break;
        }
        return {};
    }

    void KeyboardControls::onKeyDown(KeyPressedEvent &keyPressedEvent) {
        if (keyPressedEvent.repeated) return;
        velocity += accelerationOnPressed(keyPressedEvent.button);
        angularVelocity += angularAccelerationOnPressed(keyPressedEvent.button);

        const float stepSize = 0.5f;
        if (keyPressedEvent.button == Key::RIGHTBRACKET) { // US Plus
            getOwner()->get<PointCloudSprite>()->pointSize += stepSize;
        } else if (keyPressedEvent.button == Key::SLASH) { // US Minus
            PointCloudSprite * s = getOwner()->get<PointCloudSprite>();
            s->pointSize = std::max(stepSize, s->pointSize - stepSize);
        }
    }

    void KeyboardControls::onKeyReleased(KeyReleasedEvent &keyReleasedEvent) {
        velocity -= accelerationOnPressed(keyReleasedEvent.button);
        angularVelocity -= angularAccelerationOnPressed(keyReleasedEvent.button);
    }
}
