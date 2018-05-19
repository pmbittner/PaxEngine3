//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_ENGINEPLUGIN_H
#define PAXENGINE3_ENGINEPLUGIN_H

namespace PAX {
    class Engine;
    class Services;
    class Resources;
    class FactoryService;

    class EnginePlugin {
    public:
        virtual void initialize(Engine& engine) {};
        virtual void postInitialize(Engine& engine) {}
        virtual void registerServices(Services& services) {};
        virtual void registerResourceLoaders(Resources& resources) {};
        virtual void registerFactories(FactoryService& factoryService) {};
    };
}

#endif //PAXENGINE3_ENGINEPLUGIN_H
