//
// Created by Bittner on 01/04/2019.
//

#ifndef PAXENGINE3_JSONWORLDPREFABINITPARSER_H
#define PAXENGINE3_JSONWORLDPREFABINITPARSER_H

#include <paxcore/world/World.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldPrefabInitParser : public JsonEntityPrefabElementParser<World> {
        public:
            ~JsonWorldPrefabInitParser() override;
            void parse(nlohmann::json & node, World & w, JsonEntityPrefab<World> & prefab, const VariableRegister & v) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDPREFABINITPARSER_H
