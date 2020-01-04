//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_ENGINEINTERNALPLUGIN_H
#define PAXENGINE3_ENGINEINTERNALPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/rendering/scenegraph/generators/DefaultSceneGraphGeneratorFactory.h>
#include <paxcore/rendering/loader/NullTextureLoader.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>
#include <paxcore/json/JsonResourceLoader.h>

namespace PAX {
    class EngineInternalPlugin : public PAX::EnginePlugin {
        DefaultSceneGraphGeneratorFactory defaultSceneGraphGeneratorFactory;

        NullTextureLoader nullTextureLoader;
        SpriteSheetLoader spriteSheetLoader;
        JsonResourceLoader jsonLoader;

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
