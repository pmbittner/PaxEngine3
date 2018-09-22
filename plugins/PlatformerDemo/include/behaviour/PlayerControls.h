//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYERCONTROLS_H
#define PAXENGINE3_PLAYERCONTROLS_H

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/EntityComponent.h>
#include <paxcore/entity/component/Behaviour.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include <paxcore/time/Time.h>
#include "VelocityBehaviour.h"

namespace PAX {
    class PlayerControls : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PAX::Behaviour, false)
        PAX_ENTITYCOMPONENT_DEPENDS_ON(VelocityBehaviour)

        enum Direction {
            Left  = -1,
            None  =  0,
            Right =  1
        };

        std::shared_ptr<VelocityBehaviour> velocityBehaviour = nullptr;
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

        virtual void attached(Entity &entity) override {
            Behaviour::attached(entity);
            EventService& e = Services::GetEventService();
            e.add<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.add<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);

            velocityBehaviour = entity.get<VelocityBehaviour>();
        }

        virtual void detached(Entity &entity) override {
            Behaviour::detached(entity);
            EventService& e = Services::GetEventService();
            e.remove<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.remove<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);
        }
    };
}

#endif //PAXENGINE3_PLAYERCONTROLS_H
