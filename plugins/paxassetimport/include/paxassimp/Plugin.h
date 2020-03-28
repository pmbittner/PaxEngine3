//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXTEMPLATEPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXTEMPLATEPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "AssimpResourceLoader.h"

namespace PAX {
    namespace AssetImport {
        class Plugin : public PAX::EnginePlugin {
            AssimpResourceLoader assimpResourceLoader;

        public:
            void registerResourceLoaders(PAX::Resources &resources) override;
            void registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) override;
        };
    }
}

#endif //PAXENGINE3_PAXTEMPLATEPLUGIN_PLUGIN_H
