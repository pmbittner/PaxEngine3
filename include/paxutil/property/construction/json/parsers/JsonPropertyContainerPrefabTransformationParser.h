//
// Created by Bittner on 11.03.2019.
//

#ifndef PAXENGINE3_JSONPROPERTYCONTAINERPREFABTRANSFORMATIONPARSER_H
#define PAXENGINE3_JSONPROPERTYCONTAINERPREFABTRANSFORMATIONPARSER_H

#include "paxutil/property/construction/json/JsonPropertyContainerPrefab.h"

namespace PAX {
    namespace Json {
        template<typename C>
        class JsonPropertyContainerPrefabTransformationParser : public JsonPropertyContainerPrefabElementParser<C> {
        public:
            void parse(nlohmann::json & node, C & c, JsonPropertyContainerPrefab<C> & prefab, const VariableRegister & v) override {
                JsonToTransformation converter;
                converter.convert(node, c.getTransformation());
            }
        };
    }
}

#endif //PAXENGINE3_JSONPROPERTYCONTAINERPREFABTRANSFORMATIONPARSER_H
