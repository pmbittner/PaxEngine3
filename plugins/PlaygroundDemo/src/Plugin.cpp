//
// Created by Paul on 13.08.2018.
//

#include "../include/Plugin.h"

#include <core/Engine.h>

namespace PAX {
    namespace PlaygroundDemo {
        void Plugin::initialize(PAX::Engine &engine) {}

        void Plugin::postInitialize(PAX::Engine &engine) {}

        void Plugin::registerFactories(PAX::FactoryService &factoryService) {}

        void Plugin::registerResourceLoaders(PAX::Resources &resources) {}

        void Plugin::registerServices(PAX::Services &services) {}
    }
}