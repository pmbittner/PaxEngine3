//
// Created by paul on 21.09.18.
//

#ifndef PAXENGINE3_DRAGNDROP_H
#define PAXENGINE3_DRAGNDROP_H

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/service/Services.h>
#include <paxcore/entity/property/Size.h>
#include <paxcore/world/WorldLayer.h>

#include <paxcore/io/event/MouseMovedEvent.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>

namespace PAX {
    class DragNDrop : public Behaviour {
        PAX_PROPERTY(DragNDrop, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(PAX::Size)

        Size* size = nullptr;

        bool dragged = false;
        glm::vec3 relativeMousePos = {0, 0, 0};

        glm::vec3 getMouseWorldPos(Mouse* mouse) {
            const std::vector<Camera*> cams = getOwner()->getWorldLayer()->getCameras();
            // TODO: Check in which viewport the mouse is to determine the camera instead of using always camera 0.
            return {Mouse::ScreenPosToWorldPos(mouse->getScreenPosition(), *cams[0]), 0};
        }

        void onMousePressed(MouseButtonPressedEvent& e) {
            glm::vec3 mouseWorldpos = getMouseWorldPos(e.mouse);
            glm::vec3 pos = getOwner()->getTransformation().position();
            relativeMousePos = mouseWorldpos - pos;

            if (size->toAbsoluteBoundingBox().contains(relativeMousePos)) {
                dragged = true;
            }
        }

        void onMouseReleased(MouseButtonReleasedEvent& e) {
            dragged = false;
        }

    public:
        DragNDrop() = default;

        void activated() override {
            EventService& e = Services::GetEventService();
            e.add<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.add<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);

            size = getOwner()->get<Size>();
        }

        void deactivated() override {
            EventService& e = Services::GetEventService();
            e.remove<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.remove<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);

            size = nullptr;
        }

        void update(UpdateOptions & options) override {
            Super::update(options);

            if (dragged) {
                getOwner()->getTransformation().position() = getMouseWorldPos(Services::GetInput().getMouse()) - relativeMousePos;
            }
        }
    };
}

#endif //PAXENGINE3_DRAGNDROP_H
