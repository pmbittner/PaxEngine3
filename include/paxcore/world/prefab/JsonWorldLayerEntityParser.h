//
// Created by Paul on 22.06.2019.
//

#ifndef PAXENGINE3_JSONWORLDLAYERENTITYPARSER_H
#define PAXENGINE3_JSONWORLDLAYERENTITYPARSER_H

#include <paxcore/world/WorldLayer.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefab.h>

namespace PAX {
    namespace Json {
        class JsonWorldLayerEntityParser : public JsonPropertyContainerPrefabElementParser<WorldLayer> {
        public:
            ~JsonWorldLayerEntityParser() override;
            void parse(nlohmann::json & node, WorldLayer & c, JsonPropertyContainerPrefab<WorldLayer> & prefab) override;
        };
    }
}

#endif //PAXENGINE3_JSONWORLDLAYERENTITYPARSER_H
