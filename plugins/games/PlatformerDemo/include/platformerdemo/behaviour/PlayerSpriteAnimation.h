//
// Created by Paul on 14.01.2018.
//

#ifndef PAXENGINE3_PLAYERSPRITEANIMATION_H
#define PAXENGINE3_PLAYERSPRITEANIMATION_H

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/animation/Animation.h>
#include <paxutil/math/Functions.h>

#include "paxcore/gameentity/property/behaviours/2d/Movement2D.h"

namespace PAX {
    class PlayerSpriteAnimation : public Behaviour {
        PAX_PROPERTY(PlayerSpriteAnimation, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(PAX::Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(SpriteSheetGraphics, Movement2D)

        Animation<int> walkingAnimation;
        Animation<int> idleAnimation;
        Animation<int>* activeAnimation;

        int xIndex;
        int yIndex;

        int moving = 0;

        Movement2D * v = nullptr;
        SpriteSheetGraphics * spriteSheet = nullptr;

    public:
        PlayerSpriteAnimation() :
                walkingAnimation(1, 7, 0.8, &xIndex),
                idleAnimation(0, 2, 0.6, &xIndex),
                xIndex(0),
                yIndex(2),
                activeAnimation(&idleAnimation)
        {

        }

        void spawned() override {
            Behaviour::spawned();
            v = getOwner()->get<Movement2D>();
            spriteSheet = getOwner()->get<SpriteSheetGraphics>();
            idleAnimation.start();
        }

        void update(UpdateOptions & options) override {
            int oldMoving = moving;
            moving = Math::sign(v->velocity.x);
            if (oldMoving != moving) {
                Transformation & t = getOwner()->getTransformation();
                float scaleX = 0;
                if (moving) {
                    idleAnimation.stop();
                    walkingAnimation.start();
                    activeAnimation = &walkingAnimation;
                    scaleX = t.getScale().x * moving;
                    yIndex = 1;
                } else {
                    walkingAnimation.stop();
                    idleAnimation.start();
                    activeAnimation = &idleAnimation;
                    scaleX = abs(t.getScale().x);
                    yIndex = 2;
                }
                t.setScale(glm::vec3(scaleX, t.getScale().y, t.getScale().z));
            }

            activeAnimation->update();
            spriteSheet->setSpritePosition(xIndex, yIndex);
        }
    };
}

#endif //PAXENGINE3_PLAYERSPRITEANIMATION_H
