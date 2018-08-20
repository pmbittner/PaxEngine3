//
// Created by Paul on 13.08.2018.
//

#include "../include/Plugin.h"

#include <core/Engine.h>

namespace PAX {
    namespace Assimp {
        void Plugin::initialize(PAX::Engine &engine) {
            std::cout << "[PaxTemplatePlugin::Plugin::initialize]" << std::endl;
        }

        void Plugin::postInitialize(PAX::Engine &engine) {
            std::cout << "[PaxTemplatePlugin::Plugin::postInitialize]" << std::endl;
        }

        void Plugin::registerFactories(PAX::FactoryService &factoryService) {
            std::cout << "[PaxTemplatePlugin::Plugin::registerFactories]" << std::endl;
        }

        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            std::cout << "[PaxTemplatePlugin::Plugin::registerResourceLoaders]" << std::endl;
        }

        void Plugin::registerServices(PAX::Services &services) {
            std::cout << "[PaxTemplatePlugin::Plugin::registerServices]" << std::endl;
        }
    }
}