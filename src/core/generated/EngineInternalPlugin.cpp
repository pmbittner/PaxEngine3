//
// Created by Paul on 13.08.2018.
//

#include <core/generated/EngineInternalPlugin.h>

namespace PAX {
    void EngineInternalPlugin::initialize(PAX::Engine &engine) {
        std::cout << "[PAX::EngineInternalPlugin::initialize]" << std::endl;
    }

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        std::cout << "[PAX::EngineInternalPlugin::postInitialize]" << std::endl;
    }

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {
        std::cout << "[PAX::EngineInternalPlugin::registerFactories]" << std::endl;
    }

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {
        std::cout << "[PAX::EngineInternalPlugin::registerResourceLoaders]" << std::endl;
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {
        std::cout << "[PAX::EngineInternalPlugin::registerServices]" << std::endl;
    }
}