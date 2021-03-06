//
// Created by Bittner on 11/03/2019.
//

#ifndef PAXENGINE3_JSONTOTRANSFORMATION_H
#define PAXENGINE3_JSONTOTRANSFORMATION_H

#include <polypropylene/serialisation/json/nlohmann/JsonFwd.h>
#include <paxutil/math/Transformation.h>

namespace PAX {
    // TODO: Use the actual json interface
    namespace Json {
        class JsonToTransformation {
        public:
            JsonToTransformation();

            void convert(const nlohmann::json & node, Transformation & t);
        };
    }
}

#endif //PAXENGINE3_JSONTOTRANSFORMATION_H
