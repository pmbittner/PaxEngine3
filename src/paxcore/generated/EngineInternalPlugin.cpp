//
// Created by Paul on 13.08.2018.
//

#include <paxcore/generated/EngineInternalPlugin.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>
#include <paxutil/resources/Resources.h>
#include <paxutil/json/JsonLoader.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefabLoader.h>
#include <paxutil/property/construction/json/parsers/JsonPropertyContainerPrefabTransformationParser.h>
#include <paxcore/entity/Entity.h>
#include <paxcore/service/Services.h>

namespace PAX {
    void EngineInternalPlugin::initialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        static Json::JsonPropertyContainerPrefabTransformationParser<Entity> transformationParser;

        Json::JsonPropertyContainerPrefab<Entity>::initialize(Services::GetResources());
        Json::JsonPropertyContainerPrefab<Entity>::Parsers.registerParser("Transform", &transformationParser);
        EntityPrefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().toString();
        EntityPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().toString();
    }

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {}

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {
        static SpriteSheetLoader spriteSheetLoader;
        resources.registerLoader(&spriteSheetLoader);
        
        static Json::JsonLoader jsonLoader;
        resources.registerLoader(&jsonLoader);
        
        static Json::JsonPropertyContainerPrefabLoader<Entity> entityFromJsonLoader(resources);
        resources.registerLoader(&entityFromJsonLoader);
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {

    }
}