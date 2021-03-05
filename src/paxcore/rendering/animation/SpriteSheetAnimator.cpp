//
// Created by Paul Bittner on 05.03.2021.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include "paxcore/rendering/animation/SpriteSheetAnimator.h"

namespace PAX {
    PAX_PROPERTY_IMPL(SpriteSheetAnimator)

    SpriteSheetAnimator::SpriteSheetAnimator() = default;

    SpriteSheetAnimator::SpriteSheetAnimator(const std::shared_ptr<SpriteSheetAnimations> & animations, SpriteSheetAnimations::AnimationName startAnimation)
    : animations(animations), startAnimation(startAnimation) {}

    ClassMetadata SpriteSheetAnimator::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(startAnimation));
        m.add(paxfieldof(animations)).addFlag(Field::IsMandatory | EngineFieldFlags::IsResource);
        return m;
    }

    void SpriteSheetAnimator::setCurrentAnimationTo(const SpriteSheetAnimations::AnimationName &name) {
        currentAnimation = animations->getAnimationFor(name);
        currentAnimationName = name;
        currentAnimation->start();
    }

    const SpriteSheetAnimations::AnimationName & SpriteSheetAnimator::getCurrentAnimationName() const {
        return currentAnimationName;
    }

    void SpriteSheetAnimator::update(UpdateOptions &options) {
        graphics->setSpritePosition(currentAnimation->getValue());
    }

    void SpriteSheetAnimator::attached(GameEntity &entity) {
        setCurrentAnimationTo(startAnimation);
        graphics = entity.get<SpriteSheetGraphics>();
    }

    void SpriteSheetAnimator::detached(GameEntity &entity) {
        graphics = nullptr;
    }
}