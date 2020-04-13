//
// Created by Paul Bittner on 13.04.2020.
//

#include "meshfold/properties/MeshControls.h"

namespace PAX {
    PAX_PROPERTY_IMPL(MeshControls)

    ClassMetadata MeshControls::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(mouseSensivityInRadiansPerPixel));
        m.add(paxfieldof(scrollSensivity));
        return m;
    }

    void MeshControls::setExhibit(PAX::GameEntity *exhibit) {
        this->exhibit = exhibit;
    }

    void MeshControls::setCamera(PAX::GameEntity *camera) {
        this->camera = camera;
    }

    void MeshControls::attached(PAX::World & w) {
        EventService& e = Services::GetEventService();
        e.add<MouseButtonPressedEvent, MeshControls, &MeshControls::onMousePressed>(this);
        e.add<MouseButtonReleasedEvent, MeshControls, &MeshControls::onMouseReleased>(this);
        e.add<MouseWheelEvent, MeshControls, &MeshControls::onMouseWheel>(this);
    }

    void MeshControls::detached(PAX::World & w) {
        EventService& e = Services::GetEventService();
        e.remove<MouseButtonPressedEvent, MeshControls, &MeshControls::onMousePressed>(this);
        e.remove<MouseButtonReleasedEvent, MeshControls, &MeshControls::onMouseReleased>(this);
        e.remove<MouseWheelEvent, MeshControls, &MeshControls::onMouseWheel>(this);
        e.remove<MouseMovedEvent, MeshControls, &MeshControls::onMouseDragged>(this);
    }

    void MeshControls::onMousePressed(PAX::MouseButtonPressedEvent &e) {
        if (e.button == MouseButton::RIGHT) {
            Services::GetEventService().add<MouseMovedEvent, MeshControls, &MeshControls::onMouseDragged>(this);
        }
    }

    void MeshControls::onMouseReleased(PAX::MouseButtonReleasedEvent &e) {
        if (e.button == MouseButton::RIGHT) {
            Services::GetEventService().remove<MouseMovedEvent, MeshControls, &MeshControls::onMouseDragged>(this);
        }
    }

    void MeshControls::onMouseDragged(MouseMovedEvent &e) {
        if (!exhibit) return;
        Transformation & t = exhibit->getTransformation();
        glm::quat rot = glm::quatLookAt(glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
        glm::vec2 delta = mouseSensivityInRadiansPerPixel * glm::vec2(e.mouse->getScreenPosition() - e.oldScreenPos);
        totalRot += delta;
        totalRot.y = std::clamp(totalRot.y, -glm::half_pi<float>(), glm::half_pi<float>());
        rot = glm::rotate(rot, totalRot.x, glm::vec3(0, 1, 0));
        rot = glm::rotate(rot, totalRot.y, glm::rotate(glm::vec3(1, 0, 0), -totalRot.x, glm::vec3(0, 1, 0)));
        t.setRotation(rot);
    }

    void MeshControls::onMouseWheel(PAX::MouseWheelEvent &e) {
        if (!camera) return;
        Transformation & t = camera->getTransformation();
        glm::vec3 pos = t.position();
        pos.z -= scrollSensivity * e.ticksY * log(1 + pos.z);
        t.position() = pos;
    }
}