//
// Created by Paul on 05.06.2017.
//

#ifndef PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
#define PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H

#include "../core/entity/component/Behaviour.h"
#include "../core/io/Mouse.h"
#include "../core/Engine.h"
#include "../core/io/MouseButtonPressedEvent.h"

namespace PAX {
    class MoveToMouseBehaviour : public Behaviour {
        glm::vec2 _dest;
        float _speed = 0.5f;

    public:
        virtual void attached(Entity *entity) override {
            EventService &e = Engine::GetInstance()->getEventService();
            e.add<MouseButtonPressedEvent, MoveToMouseBehaviour, &MoveToMouseBehaviour::onMousePressed>(this);
        }

        virtual void detached(Entity *entity) override {
            EventService &e = Engine::GetInstance()->getEventService();
            e.remove<MouseButtonPressedEvent, MoveToMouseBehaviour, &MoveToMouseBehaviour::onMousePressed>(this);
        }

        virtual void update() override {
            Transform &t = getOwner()->getTransform();
            glm::vec2 pos = t.xy();
            glm::vec2 v = _speed * glm::normalize(_dest - pos);
            t.setPosition(pos + v);
        }

        void onMousePressed(MouseButtonPressedEvent &e) {
            LOG(INFO) << "MB Press, Button = " << e.button;
            _dest.x = e.mouse->x;
            _dest.y = e.mouse->y;
        }
    };
}

#endif //PAXENGINE3_MOVETOMOUSEBEHAVIOUR_H
