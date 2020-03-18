//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PLAYERCONTROLS_H
#define PAXENGINE3_PLAYERCONTROLS_H

#include <paxcore/entity/GameEntity.h>
#include <paxcore/entity/GameEntityProperty.h>
#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/event/KeyPressedEvent.h>
#include <paxcore/io/event/KeyReleasedEvent.h>
#include "paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h"

namespace PAX {
    class PlayerControls : public GameEntityProperty {
        PAX_PROPERTY(PlayerControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(VelocityBehaviour2D)

        enum Direction {
            Left  = -1,
            None  =  0,
            Right =  1
        };

        VelocityBehaviour2D * velocityBehaviour = nullptr;
        float speed = 20;

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

                default: break;
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

                default: break;
            }
        }

    public:
        PlayerControls() = default;
        ~PlayerControls() override = default;

        void attached(GameEntity &entity) override {
            Super::attached(entity);
            EventService& e = Services::GetEventService();
            e.add<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.add<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);

            velocityBehaviour = entity.get<VelocityBehaviour2D>();
        }

        void detached(GameEntity &entity) override {
            Super::detached(entity);
            EventService& e = Services::GetEventService();
            e.remove<KeyPressedEvent, PlayerControls, &PlayerControls::onKeyPressed>(this);
            e.remove<KeyReleasedEvent, PlayerControls, &PlayerControls::onKeyReleased>(this);
        }
    };
}

#endif //PAXENGINE3_PLAYERCONTROLS_H
