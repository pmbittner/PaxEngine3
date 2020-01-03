//
// Created by Paul on 21.05.2019.
//

#include <paxtiles/topdown/CharacterSpriteAnimation.h>

namespace PAX::Tiles {
    PAX_PROPERTY_INIT(CharacterSpriteAnimation, PAX_PROPERTY_IS_CONCRETE)

    CharacterSpriteAnimation::CharacterSpriteAnimation() :
        Behaviour(),
        spriteSheet(nullptr),
        orientation(nullptr),
        currentAnimation(nullptr),
        spriteSheetPos(),
        // For now just hardcode for our example
        walkDown ({0, 0}, {2, 0}, 1, &spriteSheetPos, AnimationBehaviour::PINGPONG),
        walkLeft ({0, 1}, {2, 1}, 1, &spriteSheetPos, AnimationBehaviour::PINGPONG),
        walkRight({0, 2}, {2, 2}, 1, &spriteSheetPos, AnimationBehaviour::PINGPONG),
        walkUp   ({0, 3}, {2, 3}, 1, &spriteSheetPos, AnimationBehaviour::PINGPONG)
    {

    }

    CharacterSpriteAnimation::~CharacterSpriteAnimation() = default;

    CharacterSpriteAnimation * CharacterSpriteAnimation::createFromProvider(PAX::ContentProvider &) {
        return new CharacterSpriteAnimation();
    }

    void CharacterSpriteAnimation::initializeFromProvider(PAX::ContentProvider & c) {
        Behaviour::initializeFromProvider(c);
    }

    Animation<glm::ivec2> & CharacterSpriteAnimation::getAnimationFromOrientation() {
        if (orientation) {
            glm::vec2 dir = orientation->getFacingDirection();

            if (glm::abs(dir.x) > glm::abs(dir.y)) {
                if (dir.x < 0)
                    return walkLeft;
                else
                    return walkRight;
            } else {
                if (dir.y > 0)
                    return walkUp;
                else
                    return walkDown;
            }
        }

        return walkDown;
    }

    void CharacterSpriteAnimation::update(UpdateOptions & options) {
        Animation<glm::ivec2> & anim = getAnimationFromOrientation();

        if (currentAnimation != &anim) {
            if (currentAnimation)
                currentAnimation->stop();

            currentAnimation = &anim;
            anim.start();
        }

        anim.update();
        spriteSheet->setSpritePosition(spriteSheetPos);
    }

    void CharacterSpriteAnimation::attached(PAX::GameEntity &e) {
        Behaviour::attached(e);
        spriteSheet = e.get<SpriteSheetGraphics>();
        orientation = e.get<CharacterOrientation>();
    }

    void CharacterSpriteAnimation::detached(PAX::GameEntity &e) {
        Behaviour::detached(e);
        spriteSheet = nullptr;
        orientation = nullptr;
    }
}