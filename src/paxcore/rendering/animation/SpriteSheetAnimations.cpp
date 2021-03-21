//
// Created by Paul Bittner on 05.03.2021.
//

#include <paxutil/io/FileTypeChecker.h>
#include <paxcore/service/Services.h>
#include "paxcore/rendering/animation/SpriteSheetAnimations.h"
#include "paxcore/animation/json/DiscreteAnimationParser.h"

namespace PAX {
    SpriteSheetAnimations::SpriteSheetAnimations(
            const std::map<AnimationName, DiscreteAnimation<glm::ivec2>> &animations)
            : animations(animations) {}

    DiscreteAnimation<glm::ivec2> * SpriteSheetAnimations::getAnimationFor(const AnimationName &name) {
        const auto & it = animations.find(name);
        if (it != animations.end()) {
            return &it->second;
        }
        PAX_THROW_RUNTIME_ERROR("Given animation \"" << name << "\" does not exist!");
    }

    bool SpriteSheetAnimationsLoader::canLoad(Path p) const {
        static Util::FileTypeChecker supportedTypes({"json"});
        return supportedTypes.check(p);
    }

    std::shared_ptr<SpriteSheetAnimations> SpriteSheetAnimationsLoader::load(Path p) {
        std::map<SpriteSheetAnimations::AnimationName, DiscreteAnimation<glm::ivec2>> animations;

        std::shared_ptr<nlohmann::json> jptr = Services::GetResources().loadOrGet<nlohmann::json>(p);
        const nlohmann::json & j = *jptr;

        for (const auto & entry : j.items()) {
            auto name = String::convertTo<SpriteSheetAnimations::AnimationName>(entry.key());
            auto anim = Json::convertTo<DiscreteAnimation<glm::ivec2>>(entry.value());
            animations.insert_or_assign(name, anim);
        }

        return std::make_shared<SpriteSheetAnimations>(animations);
    }

    std::shared_ptr<SpriteSheetAnimations> SpriteSheetAnimationsLoader::loadOrGetFromJson(Resources &resources,
                                                                                          const nlohmann::json &j) const {
        return resources.loadOrGet<SpriteSheetAnimations>(JsonToPath(j));
    }
}