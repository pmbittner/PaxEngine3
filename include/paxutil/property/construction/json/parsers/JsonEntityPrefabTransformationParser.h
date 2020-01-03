//
// Created by Bittner on 11.03.2019.
//

#ifndef PAXENGINE3_JSONENTITYPREFABTRANSFORMATIONPARSER_H
#define PAXENGINE3_JSONENTITYPREFABTRANSFORMATIONPARSER_H

#include "polypropylene/serialisation/json/property/JsonEntityPrefab.h"

namespace PAX {
    namespace Json {
        template<typename C>
        class JsonEntityPrefabTransformationParser : public JsonEntityPrefabElementParser<C> {
        public:
            void parse(nlohmann::json & node, C & c, JsonEntityPrefab<C> & prefab, const VariableRegister & v) override {
                JsonToTransformation converter;
                converter.convert(node, c.getTransformation());
            }
        };
    }
}

#endif //PAXENGINE3_JSONENTITYPREFABTRANSFORMATIONPARSER_H
