//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYERCONTROLS_H
#define PAXENGINE3_PLAYERCONTROLS_H

#include <core/entity/Entity.h>
#include <core/entity/EntityComponent.h>
#include <core/entity/component/Behaviour.h>
#include <core/service/Services.h>
#include <core/io/event/KeyPressedEvent.h>
#include <core/io/event/KeyReleasedEvent.h>
#include <core/time/Time.h>
#include "VelocityBehaviour.h"

namespace PAX {
    class PlayerControls : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(Behaviour, false)
        PAX_ENTITYCOMPONENT_DEPENDS_ON(VelocityBehaviour)

        enum Direction {
            Left  = -1,
            None  =  0,
            Right =  1
        };

        VelocityBehaviour* velocityBehaviour = nullptr;
        float speed = 150;

        void onKeyPressed(KeyPressedEvent& e) {
            if (e.repeated) return;

            switch (e.button) {
                case Key::LEFT: {
                    velocityBehaviour->velocity.x += Left * speed;
                    break;
                }

                case Key::RIGHT: {
                    velocityBehaviour->velocity.x += Right * speed;
                    break;
                }
            }
        }

        void onKeyReleased(KeyReleasedEvent& e) {
            switch (e.button) {
                case Key::LEFT: {
                    velocityBehaviour->velocity.x -= Left * speed;
                    break;
                }

                case Key::RIGHT: {
                    velocityBehaviour->velocity.x -= Right * speed;
                    break;
                }
            }
        }

    public:
        PlayerControls() {}
        ~PlayerControls() {}

        virtual void attached(Entity *entity) override {
            Behaviour::attached(entity);
            EventService& e = Services::GetEventService();
            e.add<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.add<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);

            velocityBehaviour = entity->get<VelocityBehaviour>();
        }

        virtual void detached(Entity *entity) override {
            Behaviour::detached(entity);
            EventService& e = Services::GetEventService();
            e.remove<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.remove<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);
        }
    };
}

#endif //PAXENGINE3_PLAYERCONTROLS_H
