//
// Created by Paul Bittner on 04.03.2021.
//

#ifndef MESHFOLD_DISCRETEANIMATIONPARSER_H
#define MESHFOLD_DISCRETEANIMATIONPARSER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include "../DiscreteAnimation.h"
#include "AnimationBehaviourParser.h"

namespace PAX {
    template<typename T>
    class TryParser<nlohmann::json, DiscreteAnimation<T>> {
        using Anim = DiscreteAnimation<T>;
        static constexpr const char * FRAMES = "frames";
        static constexpr const char * TYPE = "type";
        static constexpr const char * DEFAULTFRAMEDURATION = "defaultFrameDuration";
        static constexpr const char * KEYFRAME_DURATION = "duration";
        static constexpr const char * KEYFRAME_VALUE = "value";

    public:
        PAX_NODISCARD static Anim tryParse(const nlohmann::json & j) {
            if (j.count(FRAMES) < 1) {
                PAX_THROW_RUNTIME_ERROR("No frames given for animation:\n" << JsonToString(j));
            }
            if (j.count(TYPE) < 1) {
                PAX_THROW_RUNTIME_ERROR("No AnimationBehaviour given for animation:\n" << JsonToString(j));
            }

            std::vector<typename Anim::KeyFrame> frames;

            double defaultDuration = 1.0; // seconds
            if (j.count(DEFAULTFRAMEDURATION) > 0) {
                defaultDuration = Json::tryParse<double>(j[DEFAULTFRAMEDURATION]);
            }

            for (const nlohmann::json & framejson : j[FRAMES]) {
                T val = Json::tryParse<T>(framejson[KEYFRAME_VALUE]);
                double duration = defaultDuration;
                if (framejson.count(KEYFRAME_DURATION) > 0) {
                    duration = Json::tryParse<double>(framejson[KEYFRAME_DURATION]);
                }
                frames.emplace_back(val, duration);
            }

            auto behaviour = Json::tryParse<AnimationBehaviour>(j[TYPE]);
            return Anim(frames, behaviour);
        }
    };
}

#endif //MESHFOLD_DISCRETEANIMATIONPARSER_H
