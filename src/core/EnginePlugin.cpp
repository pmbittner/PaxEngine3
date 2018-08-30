//
// Created by Paul on 30.08.2018.
//

#include <core/EnginePlugin.h>

namespace PAX {
    EnginePlugin::EnginePlugin(PAX::EnginePluginDependencies *dependencies) : dependencies(dependencies) {

    }

    void EnginePlugin::checkDependencies(const std::vector<PAX::EnginePlugin *> &plugins) const {
        if (dependencies)
            dependencies->checkDependencies(plugins);
    }
}