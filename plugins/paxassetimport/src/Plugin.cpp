//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>
#include "paxassimp/Plugin.h"

namespace PAX {
    namespace AssetImport {
        void Plugin::initialize(PAX::Engine &engine) {}

        void Plugin::postInitialize(PAX::Engine &engine) {}

        void Plugin::registerFactories(PAX::FactoryService &factoryService) {}

        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            LOG(INFO) << "[PAX::AssetImport::Plugin::registerResourceLoaders] Register AssimpResourceLoader" << std::endl;
            resources.registerLoader(&assimpResourceLoader);
        }

        void Plugin::registerServices(PAX::Services &services) {}
    }
}