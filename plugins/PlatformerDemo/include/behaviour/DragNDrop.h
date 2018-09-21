//
// Created by paul on 21.09.18.
//

#ifndef PAXENGINE3_DRAGNDROP_H
#define PAXENGINE3_DRAGNDROP_H

#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/service/Services.h>

#include <paxcore/io/event/MouseMovedEvent.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>

namespace PAX {
    class DragNDrop : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(Behaviour, false)

        void onMouseDragged(MouseMovedEvent& e) {

        }

        void onMousePressed(MouseButtonPressedEvent& e) {
            std::cout << e.mouse->getX() << ", " << e.mouse->getY() << std::endl;
        }

        void onMouseReleased(MouseButtonReleasedEvent& e) {

        }

    public:
        DragNDrop() {}

        virtual void attached(Entity& entity) override {
            EventService& e = Services::GetEventService();
            e.add<MouseMovedEvent, DragNDrop, &DragNDrop::onMouseDragged>(this);
            e.add<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.add<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);
        }

        virtual void detached(Entity& entity) override {
            EventService& e = Services::GetEventService();
            e.remove<MouseMovedEvent, DragNDrop, &DragNDrop::onMouseDragged>(this);
            e.remove<MouseButtonPressedEvent, DragNDrop, &DragNDrop::onMousePressed>(this);
            e.remove<MouseButtonReleasedEvent, DragNDrop, &DragNDrop::onMouseReleased>(this);
        }
    };
}

#endif //PAXENGINE3_DRAGNDROP_H
