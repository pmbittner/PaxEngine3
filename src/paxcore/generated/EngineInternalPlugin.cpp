//
// Created by Paul on 13.08.2018.
//

#include <paxcore/generated/EngineInternalPlugin.h>

namespace PAX {
    void EngineInternalPlugin::initialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {}

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {}

    void EngineInternalPlugin::registerServices(PAX::Services &services) {}
}