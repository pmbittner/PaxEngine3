//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include <paxphysics/2d/material/PhysicsMaterialLoader.h>

namespace PAX::Physics {
    class Plugin : public EnginePlugin {
        PhysicsMaterialLoader psxmatLoader;

    public:
        void registerProperties() override;
        void registerResourceLoaders(Resources & resources) override;
        void registerSystems(Game& game) override;
        void postInitialize(Engine & engine) override;
    };
}

#endif //PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H
