//
// Created by Paul Bittner on 04.03.2021.
//

#ifndef MESHFOLD_DISCRETEANIMATIONPARSER_H
#define MESHFOLD_DISCRETEANIMATIONPARSER_H

#include <polypropylene/serialisation/json/JsonTypeConverter.h>
#include "../DiscreteAnimation.h"
#include "AnimationBehaviourParser.h"

namespace PAX {
    template<typename T>
    class TypeConverter<nlohmann::json, DiscreteAnimation<T>> {
        using Anim = DiscreteAnimation<T>;
        static constexpr const char * FRAMES = "frames";
        static constexpr const char * TYPE = "type";
        static constexpr const char * DEFAULTFRAMEDURATION = "defaultFrameDuration";
        static constexpr const char * KEYFRAME_DURATION = "duration";
        static constexpr const char * KEYFRAME_VALUE = "value";

    public:
        PAX_NODISCARD static Anim convertTo(const nlohmann::json & j) {
            if (j.count(FRAMES) < 1) {
                PAX_THROW_RUNTIME_ERROR("No frames given for animation:\n" << JsonToString(j));
            }
            if (j.count(TYPE) < 1) {
                PAX_THROW_RUNTIME_ERROR("No AnimationBehaviour given for animation:\n" << JsonToString(j));
            }

            std::vector<typename Anim::KeyFrame> frames;

            double defaultDuration = 1.0; // seconds
            if (j.count(DEFAULTFRAMEDURATION) > 0) {
                defaultDuration = Json::convertTo<double>(j[DEFAULTFRAMEDURATION]);
            }

            for (const nlohmann::json & framejson : j[FRAMES]) {
                T val = Json::convertTo<T>(framejson[KEYFRAME_VALUE]);
                double duration = defaultDuration;
                if (framejson.count(KEYFRAME_DURATION) > 0) {
                    duration = Json::convertTo<double>(framejson[KEYFRAME_DURATION]);
                }
                frames.emplace_back(val, duration);
            }

            auto behaviour = Json::convertTo<AnimationBehaviour>(j[TYPE]);
            return Anim(frames, behaviour);
        }

        PAX_NODISCARD static nlohmann::json convertFrom(const Anim & d) {
            nlohmann::json node;
            node["type"] = Json::convertFrom(d.getBehaviour());

            nlohmann::json frames = nlohmann::json::array();
            for (const typename Anim::KeyFrame & f : d.getFrames()) {
                nlohmann::json frame;
                frame["value"] = Json::convertFrom(f.value);
                frame["duration"] = f.duration.count();
                frames.push_back(frame);
            }
            node["frames"] = frames;
            return node;
        }
    };
}

#endif //MESHFOLD_DISCRETEANIMATIONPARSER_H
