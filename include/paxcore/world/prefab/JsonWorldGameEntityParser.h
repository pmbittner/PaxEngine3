//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_JSONWORLDGAMEENTITYPARSER_H
#define PAXENGINE3_JSONWORLDGAMEENTITYPARSER_H

#include <paxcore/world/World.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldGameEntityParser : public JsonEntityPrefabElementParser<World> {
        public:
            ~JsonWorldGameEntityParser() override;
            void parse(nlohmann::json & node, World & w, JsonEntityPrefab<World> & prefab, const VariableRegister & v) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDGAMEENTITYPARSER_H
