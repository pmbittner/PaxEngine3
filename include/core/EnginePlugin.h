//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_ENGINEPLUGIN_H
#define PAXENGINE3_ENGINEPLUGIN_H

#include <core/reflection/EntityComponentReflectionData.h>

namespace PAX {
    class Engine;
    class Services;
    class Resources;
    class FactoryService;
    namespace Reflection {
        class TypeHierarchy;
    }

    class EnginePlugin {
    public:
        virtual void initialize(Engine& engine) {};
        virtual void postInitialize(Engine& engine) {}
        virtual void registerServices(Services& services) {};
        virtual void registerResourceLoaders(Resources& resources) {};
        virtual void registerFactories(FactoryService& factoryService) {};

        virtual void internal_initializeReflectionData(EntityComponentReflectionData& reflectionData) {};
    };
}

#define PAX_ENGINEPLUGIN_CONTAINS_ENTITYCOMPONENTS \
public: \
virtual void internal_initializeReflectionData(PAX::EntityComponentReflectionData &reflectionData) override; \
private:

#endif //PAXENGINE3_ENGINEPLUGIN_H
