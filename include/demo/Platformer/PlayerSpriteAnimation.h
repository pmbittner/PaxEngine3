//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_PLAYERSPRITEANIMATION_H
#define PAXENGINE3_PLAYERSPRITEANIMATION_H

#include <core/entity/component/Behaviour.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>

namespace PAX {
    namespace Platformer { class PlayerSpriteAnimation; }
    PAX_ENTITYCOMPONENT_DERIVED(Platformer::PlayerSpriteAnimation, Behaviour, SpriteSheetGraphics)
    namespace Platformer {
        class PlayerSpriteAnimation : public Behaviour {
            PAX_ENTITYCOMPONENT_BODY
        public:
            virtual void attached(Entity *entity) override {

            }

            virtual void update() override {
                Transform &t = getOwner()->getTransform();
                t.rotation2D() += 0.01f;
            }
        };
    }
}

#endif //PAXENGINE3_PLAYERSPRITEANIMATION_H
