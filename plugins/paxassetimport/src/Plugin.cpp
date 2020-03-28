//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>
#include <paxutil/resources/JsonResourceFieldWriter.h>
#include "paxassimp/Plugin.h"

namespace PAX {
    namespace AssetImport {
        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            resources.registerLoader(&assimpResourceLoader);
        }

        void Plugin::registerJsonWriters(Json::JsonFieldWriterRegister &writerRegister) {
            static JsonResourceFieldWriter<Asset> assetWriter;
            assetWriter.registerAt(writerRegister);
        }
    }
}