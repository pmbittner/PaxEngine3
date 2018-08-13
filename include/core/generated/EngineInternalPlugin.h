//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_ENGINEINTERNALPLUGIN_H
#define PAXENGINE3_ENGINEINTERNALPLUGIN_H

#include <core/EnginePlugin.h>

namespace PAX {
    class EngineInternalPlugin : public PAX::EnginePlugin {
    public:
        virtual void initialize(PAX::Engine& engine) override;
        virtual void postInitialize(PAX::Engine& engine) override;

        virtual void registerServices(PAX::Services& services) override;
        virtual void registerResourceLoaders(PAX::Resources& resources) override;
        virtual void registerFactories(PAX::FactoryService& factoryService) override;

        virtual void internal_initializeReflectionData(PAX::EntityComponentReflectionData& reflectionData) override;
    };
}

#endif //PAXENGINE3_ENGINEINTERNALPLUGIN_H
