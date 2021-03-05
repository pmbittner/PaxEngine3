//
// Created by Paul Bittner on 05.03.2021.
//

#ifndef MESHFOLD_SPRITESHEETANIMATIONS_H
#define MESHFOLD_SPRITESHEETANIMATIONS_H

#include <polypropylene/io/Path.h>
#include "paxcore/animation/DiscreteAnimation.h"
#include "paxutil/lib/GlmIncludes.h"
#include "paxutil/resources/ResourceLoader.h"

namespace PAX {
    class SpriteSheetAnimations {
    public:
        using AnimationName = std::string;

    private:
        std::map<AnimationName, DiscreteAnimation<glm::ivec2>> animations;

    public:
        explicit SpriteSheetAnimations(const std::map<AnimationName, DiscreteAnimation<glm::ivec2>> & animations);
        PAX_NODISCARD DiscreteAnimation<glm::ivec2> * getAnimationFor(const AnimationName & name);
    };

    class SpriteSheetAnimationsLoader : public ResourceLoader<SpriteSheetAnimations, Path> {
    public:
        PAX_NODISCARD std::shared_ptr<SpriteSheetAnimations> loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const override;
        PAX_NODISCARD bool canLoad(Path p) const override;
        PAX_NODISCARD std::shared_ptr<SpriteSheetAnimations> load(Path p) override;
    };
}

#endif //MESHFOLD_SPRITESHEETANIMATIONS_H
