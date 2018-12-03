//
// Created by paul on 21.09.18.
//

#ifndef PAXENGINE3_DRAGNDROP_H
#define PAXENGINE3_DRAGNDROP_H

#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/service/Services.h>
#include <paxcore/entity/component/Size.h>
#include <paxcore/world/WorldLayer.h>

#include <paxcore/io/event/MouseMovedEvent.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>

namespace PAX {
    class DragNDrop : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(Behaviour, false)
        PAX_ENTITYCOMPONENT_DEPENDS_ON(PAX::Size)

        std::shared_ptr<Size> size;

        bool dragged = false;
        glm::vec3 relativeMousePos;

        glm::vec3 getMouseWorldPos(Mouse* mouse) {
            const std::vector<std::shared_ptr<Camera>> cams = getOwner()->getWorldLayer()->getCameras();
            return {Mouse::ScreenPosToWorldPos(mouse->getScreenPosition(), *cams[0].get()), 0};
        }

        void onMouseDragged(MouseMovedEvent& e) {
            if (dragged) {
                getOwner()->getTransformation().position() = getMouseWorldPos(e.mouse) - relativeMousePos;
            }
        }

        void onMousePressed(MouseButtonPressedEvent& e) {
            glm::vec3 mouseWorldpos = getMouseWorldPos(e.mouse);
            glm::vec3 pos = getOwner()->getTransformation().position();
            relativeMousePos = mouseWorldpos - pos;

            if (size->toAbsoluteBoundingBox().contains(&relativeMousePos[0])) {
                dragged = true;
            }
        }

        void onMouseReleased(MouseButtonReleasedEvent& e) {
            dragged = false;
        }

    public:
        DragNDrop() {}

        virtual void attached(Entity& entity) override {
            EventService& e = Services::GetEventService();
            e.add<MouseMovedEvent, DragNDrop, &DragNDrop::onMouseDragged>(this);
            e.add<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.add<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);

            size = entity.get<Size>();
        }

        virtual void detached(Entity& entity) override {
            EventService& e = Services::GetEventService();
            e.remove<MouseMovedEvent, DragNDrop, &DragNDrop::onMouseDragged>(this);
            e.remove<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.remove<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);

            size = nullptr;
        }
    };
}

#endif //PAXENGINE3_DRAGNDROP_H
