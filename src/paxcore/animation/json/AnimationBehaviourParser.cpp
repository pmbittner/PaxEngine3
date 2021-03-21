//
// Created by Paul Bittner on 04.03.2021.
//

#include "paxcore/animation/json/AnimationBehaviourParser.h"
#include "polypropylene/serialisation/json/nlohmann/Json.h"

namespace PAX {
    PAX_IMPLEMENT_JSON_CONVERT_TO(AnimationBehaviour) {
        const std::string str = String::LowerCase(JsonToString(x));
        if ("once" == str) {
            return AnimationBehaviour::ONCE;
        } else if ("loop" == str) {
            return AnimationBehaviour::LOOP;
        } else if ("pingpong" == str) {
            return AnimationBehaviour::PINGPONG;
        }

        PAX_THROW_RUNTIME_ERROR("Could not parse AnimationBehaviour from \"" << str << "\"!");
    }

    PAX_IMPLEMENT_JSON_CONVERT_FROM_WITH_OSTREAM(AnimationBehaviour)
}