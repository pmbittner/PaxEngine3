//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
#define PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H

#include "../../core/entity/component/Behaviour.h"
#include "../../core/io/Mouse.h"
#include "../../core/Engine.h"
#include "core/io/event/MouseButtonPressedEvent.h"
#include "../../core/time/Time.h"
#include "core/service/Services.h"

namespace PAX {
    PAX_ENTITYCOMPONENT_DERIVED(MoveToMouseBehaviour, Behaviour)
    class MoveToMouseBehaviour : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY

        glm::vec2 _dest;
        float _speed = 100.0f;

    public:
        MoveToMouseBehaviour() {
            _dest = glm::vec2(0, 0);
        }

        virtual void attached(Entity *entity) override {
            EventService &e = Services::GetEventService();
            e.add<MouseButtonPressedEvent, MoveToMouseBehaviour, &MoveToMouseBehaviour::onMousePressed>(this);
        }

        virtual void detached(Entity *entity) override {
            EventService &e = Services::GetEventService();
            e.remove<MouseButtonPressedEvent, MoveToMouseBehaviour, &MoveToMouseBehaviour::onMousePressed>(this);
        }

        virtual void update() override {
            Transform &t = getOwner()->getTransform();
            glm::vec2 pos = t.getPosition2D();
            if (_dest != pos) {
                glm::vec2 dist = _dest - pos;
                if (glm::length(dist) < 2.f) {
                    t.position2D() = _dest;
                } else {
                    glm::vec2 v = _speed * Time::DeltaF * glm::normalize(dist);
                    t.position2D() = pos + v;
                }
            }
        }

        void onMousePressed(MouseButtonPressedEvent &e) {
            LOG(INFO) << "Mouse pressed at " << e.mouse->getX() << " / " << e.mouse->getY();
            _dest.x = e.mouse->getX() - 400;
            _dest.y = 300 - e.mouse->getY();
        }
    };
}

#endif //PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
