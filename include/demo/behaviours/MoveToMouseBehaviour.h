//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
#define PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H

#include "../../core/entity/component/Behaviour.h"
#include "../../core/io/Mouse.h"
#include "../../core/Engine.h"
#include "../../core/io/MouseButtonPressedEvent.h"
#include "../../core/time/Time.h"
#include "../../core/Services.h"

namespace PAX {
    class MoveToMouseBehaviour : public Behaviour {
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
            glm::vec2 pos = t.xy();
            if (_dest != pos) {
                glm::vec2 dist = _dest - pos;
                if (glm::length(dist) < 2.f) {
                    t.setPosition(_dest);
                } else {
                    glm::vec2 n = glm::normalize(dist);
                    glm::vec2 v = _speed * Time::DeltaF * n;
                    t.setPosition(pos + v);
                }
            }
        }

        void onMousePressed(MouseButtonPressedEvent &e) {
            LOG(INFO) << "MB " << e.button << " pressed at " << e.mouse->x << " / " << e.mouse->y;
            _dest.x = e.mouse->x - 400;
            _dest.y = 300 - e.mouse->y;
        }
    };
}

#endif //PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
