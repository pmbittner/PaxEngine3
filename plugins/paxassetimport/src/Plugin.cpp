//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>
#include "paxassimp/Plugin.h"
#include <paxutil/log/Log.h>

namespace PAX {
    namespace AssetImport {
        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            Log::out.info() << "[PAX::AssetImport::Plugin::registerResourceLoaders] Register AssimpResourceLoader" << std::endl;
            resources.registerLoader(&assimpResourceLoader);
        }
    }
}