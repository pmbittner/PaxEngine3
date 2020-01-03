//
// Created by Bittner on 01/04/2019.
//

#ifndef PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H
#define PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H

#include <paxcore/world/WorldLayer.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldLayerPrefabInitParser : public JsonEntityPrefabElementParser<WorldLayer> {
        public:
            ~JsonWorldLayerPrefabInitParser() override;
            void parse(nlohmann::json & node, WorldLayer & c, JsonEntityPrefab<WorldLayer> & prefab, const VariableRegister & v) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDLAYERPREFABINITPARSER_H
