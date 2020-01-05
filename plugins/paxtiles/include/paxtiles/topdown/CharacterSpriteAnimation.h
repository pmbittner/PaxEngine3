//
// Created by Paul on 21.05.2019.
//

#ifndef PAXENGINE3_CHARACTERSPRITEANIMATION_H
#define PAXENGINE3_CHARACTERSPRITEANIMATION_H

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/animation/Animation.h>

#include "CharacterOrientation.h"

namespace PAX::Tiles {
    class CharacterSpriteAnimation : public Behaviour {
        PAX_PROPERTY(CharacterSpriteAnimation, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(SpriteSheetGraphics, CharacterOrientation)

        SpriteSheetGraphics  * spriteSheet;
        CharacterOrientation * orientation;

        Animation<glm::ivec2> * currentAnimation;

    protected:
        glm::ivec2 spriteSheetPos;

        // TODO: Allow arbitrarily many animations for given directions.
        Animation<glm::ivec2> walkUp;
        Animation<glm::ivec2> walkLeft;
        Animation<glm::ivec2> walkRight;
        Animation<glm::ivec2> walkDown;

        virtual Animation<glm::ivec2> & getAnimationFromOrientation();

    public:
        CharacterSpriteAnimation();
        ~CharacterSpriteAnimation() override;

        void update(UpdateOptions & options) override;
        void attached(GameEntity & e) override;
        void detached(GameEntity & e) override;
    };
}

#endif //PAXENGINE3_CHARACTERSPRITEANIMATION_H
