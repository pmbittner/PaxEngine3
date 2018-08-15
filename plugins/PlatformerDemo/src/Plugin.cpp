//
// Created by Paul on 13.08.2018.
//

#include "../include/Plugin.h"

#include <core/Engine.h>

namespace PAX {
    namespace PlatformerDemo {
        void Plugin::initialize(PAX::Engine &engine) {
            std::cout << "[Pax::Platformer::Plugin::initialize]" << std::endl;
        }

        void Plugin::postInitialize(PAX::Engine &engine) {
            std::cout << "[Pax::Platformer::Plugin::postInitialize]" << std::endl;
        }

        void Plugin::registerFactories(PAX::FactoryService &factoryService) {
            std::cout << "[Pax::Platformer::Plugin::registerFactories]" << std::endl;
        }

        void Plugin::registerResourceLoaders(PAX::Resources &resources) {
            std::cout << "[Pax::Platformer::Plugin::registerResourceLoaders]" << std::endl;
        }

        void Plugin::registerServices(PAX::Services &services) {
            std::cout << "[Pax::Platformer::Plugin::registerServices]" << std::endl;
        }
    }
}