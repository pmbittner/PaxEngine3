//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_PLAYERSPRITEANIMATION_H
#define PAXENGINE3_PLAYERSPRITEANIMATION_H

#include <core/entity/component/Behaviour.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>

namespace PAX {
    PAX_ENTITYCOMPONENT_DERIVED(PlayerSpriteAnimation, Behaviour)
    class PlayerSpriteAnimation : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY(PlayerSpriteAnimation)
        PAX_ENTITYCOMPONENT_DEPENDS_ON(Behaviour, SpriteSheetGraphics)
    public:
        virtual void attached(Entity *entity) override {

        }

        virtual void update() override {
            Transform &t = getOwner()->getTransform();
            //t.rotation2D() += 0.01f;
        }
    };
}

#endif //PAXENGINE3_PLAYERSPRITEANIMATION_H
