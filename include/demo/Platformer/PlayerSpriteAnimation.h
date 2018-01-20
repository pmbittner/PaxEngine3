//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_PLAYERSPRITEANIMATION_H
#define PAXENGINE3_PLAYERSPRITEANIMATION_H

#include <core/entity/component/Behaviour.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>
#include <core/animation/Animation.h>
#include <utility/math/Functions.h>

namespace PAX {
    PAX_ENTITYCOMPONENT(PlayerSpriteAnimation, Behaviour, false)
    class PlayerSpriteAnimation : public Behaviour {
        PAX_ENTITYCOMPONENT_BODY
        PAX_ENTITYCOMPONENT_DEPENDS_ON(Behaviour, SpriteSheetGraphics, VelocityBehaviour)

        Animation<int> walkingAnimation;
        Animation<int> idleAnimation;
        Animation<int>* activeAnimation;

        int xIndex;
        int yIndex;

        int moving = 0;
        VelocityBehaviour *v;

        SpriteSheetGraphics *spriteSheet;

    public:
        PlayerSpriteAnimation() :
                walkingAnimation(1, 7, 0.8, &xIndex),
                idleAnimation(0, 2, 0.6, &xIndex),
                xIndex(0),
                yIndex(2),
                activeAnimation(&idleAnimation)
        {

        }

        virtual void attached(Entity *entity) override {
            v = entity->get<VelocityBehaviour>();
            spriteSheet = entity->get<SpriteSheetGraphics>();
            idleAnimation.start();
        }

        virtual void update() override {
            int oldMoving = moving;
            moving = Math::sign(v->velocity.x);
            if (oldMoving != moving) {
                if (moving) {
                    idleAnimation.stop();
                    walkingAnimation.start();
                    activeAnimation = &walkingAnimation;
                    getOwner()->getTransform().scaleX() = moving;
                    yIndex = 1;
                } else {
                    walkingAnimation.stop();
                    idleAnimation.start();
                    activeAnimation = &idleAnimation;
                    getOwner()->getTransform().scaleX() = 1;
                    yIndex = 2;
                }
            }

            activeAnimation->update();
            spriteSheet->setSpritePosition(xIndex, yIndex);
        }
    };
}

#endif //PAXENGINE3_PLAYERSPRITEANIMATION_H
