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

namespace PAX {
    PAX_ENTITYCOMPONENT_DERIVED(PlayerControls, Behaviour)
    class PlayerControls : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PlayerControls)

        enum Direction {
            Left  = -1,
            None  =  0,
            Right =  1
        };

        int _walkingDirection = None;
        float speed = 150;

        void onKeyPressed(KeyPressedEvent& e) {
            if (e.repeated) return;

            switch (e.button) {
                case Key::LEFT: {
                    _walkingDirection += Left;
                    break;
                }

                case Key::RIGHT: {
                    _walkingDirection += Right;
                    break;
                }
            }
        }

        void onKeyReleased(KeyReleasedEvent& e) {
            switch (e.button) {
                case Key::LEFT: {
                    _walkingDirection -= Left;
                    break;
                }

                case Key::RIGHT: {
                    _walkingDirection -= Right;
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
        }

        virtual void detached(Entity *entity) override {
            Behaviour::detached(entity);
            EventService& e = Services::GetEventService();
            e.remove<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.remove<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);
        }

        virtual void update() override {
            Transform& t = getOwner()->getTransform();
            t.x() += _walkingDirection * speed * Time::DeltaF;
        }
    };
}

#endif //PAXENGINE3_PLAYERCONTROLS_H
