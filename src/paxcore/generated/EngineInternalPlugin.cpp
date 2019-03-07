//
// Created by Paul on 13.08.2018.
//

#include <paxcore/generated/EngineInternalPlugin.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>
#include <paxutil/resources/Resources.h>
#include <paxutil/json/JsonLoader.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefabLoader.h>
#include <paxcore/entity/Entity.h>
#include <paxcore/service/Services.h>

namespace PAX {
    void EngineInternalPlugin::initialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        JsonPropertyContainerPrefab<Entity>::initialize(Services::GetResources());
        EntityPrefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().toString();
        EntityPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().toString();
    }

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {}

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {
        static SpriteSheetLoader spriteSheetLoader;
        resources.registerLoader(&spriteSheetLoader);
        
        static JsonLoader jsonLoader;
        resources.registerLoader(&jsonLoader);
        
        static JsonPropertyContainerPrefabLoader<Entity> entityFromJsonLoader(resources);
        resources.registerLoader(&entityFromJsonLoader);
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {

    }
}