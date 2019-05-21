//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_ENGINEINTERNALPLUGIN_H
#define PAXENGINE3_ENGINEINTERNALPLUGIN_H

#include <paxcore/EnginePlugin.h>

namespace PAX {
    class EngineInternalPlugin : public PAX::EnginePlugin {
    public:
        void initialize(PAX::Engine& engine) override;
        void postInitialize(PAX::Engine& engine) override;

        void registerServices(PAX::Services& services) override;
        void registerResourceLoaders(PAX::Resources& resources) override;
        void registerFactories(PAX::FactoryService& factoryService) override;
        void registerProperties() override;
    };
}

#endif //PAXENGINE3_ENGINEINTERNALPLUGIN_H
