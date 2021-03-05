//
// Created by Paul Bittner on 05.03.2021.
//

#ifndef PAXENGINE3_SPRITESHEETANIMATOR_H
#define PAXENGINE3_SPRITESHEETANIMATOR_H

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/animation/DiscreteAnimation.h>
#include "../graphics/SpriteSheetGraphics.h"
#include "SpriteSheetAnimations.h"

namespace PAX {
    class SpriteSheetAnimator : public Behaviour {
        PAX_PROPERTY(SpriteSheetAnimator, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(Behaviour)
        PAX_PROPERTY_IS_SINGLE
        PAX_PROPERTY_DEPENDS_ON(SpriteSheetGraphics)

    private:
        /// BEGIN FIELDS
        std::shared_ptr<SpriteSheetAnimations> animations;
        SpriteSheetAnimations::AnimationName startAnimation;
        /// END FIELDS

        SpriteSheetGraphics * graphics = nullptr;
        DiscreteAnimation<glm::ivec2>* currentAnimation = nullptr;
        SpriteSheetAnimations::AnimationName currentAnimationName;

        SpriteSheetAnimator();

    public:
        explicit SpriteSheetAnimator(const std::shared_ptr<SpriteSheetAnimations> & animations, SpriteSheetAnimations::AnimationName startAnimation);

        PAX_NODISCARD ClassMetadata getMetadata() override;

        void update(UpdateOptions & options) override;

        void setCurrentAnimationTo(const SpriteSheetAnimations::AnimationName & name);
        PAX_NODISCARD const SpriteSheetAnimations::AnimationName & getCurrentAnimationName() const;

        void attached(GameEntity & entity) override;
        void detached(GameEntity & entity) override;
    };
}

#endif //PAXENGINE3_SPRITESHEETANIMATOR_H
