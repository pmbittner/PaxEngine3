//
// Created by Paul on 13.08.2018.
//

#include <paxcore/generated/EngineInternalPlugin.h>
#include <paxcore/rendering/loader/SpriteSheetLoader.h>

#include <paxutil/resources/Resources.h>
#include <paxutil/json/JsonLoader.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefabLoader.h>
#include <paxutil/property/construction/json/parsers/JsonPropertyContainerPrefabTransformationParser.h>

#include <paxcore/world/prefab/JsonWorldLayerPrefabInitParser.h>
#include <paxcore/entity/Entity.h>
#include <paxcore/world/WorldLayer.h>
#include <paxcore/service/Services.h>

#include <paxcore/entity/property/Behaviour.h>
#include <paxcore/entity/property/Size.h>
#include <paxcore/entity/property/behaviours/NoClipControls.h>
#include <paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h>
#include <paxcore/entity/property/behaviours/2d/FollowEntityBehaviour.h>
#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/rendering/light/AmbientLight.h>
#include <paxcore/rendering/light/DirectionalLight.h>
#include <paxcore/rendering/light/SpotLight.h>
#include <paxcore/rendering/light/PointLight.h>
#include <paxcore/world/property/WorldLayerBehaviour.h>

namespace PAX {
    void EngineInternalPlugin::initialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        static Json::JsonPropertyContainerPrefabTransformationParser<Entity> transformationParser;
        static Json::JsonWorldLayerPrefabInitParser worldLayerPrefabInitParser;

        Json::JsonPropertyContainerPrefab<Entity>::initialize(Services::GetResources());
        Json::JsonPropertyContainerPrefab<WorldLayer>::initialize(Services::GetResources());

        Json::JsonPropertyContainerPrefab<Entity>::Parsers.registerParser("Transform", &transformationParser);
        Json::JsonPropertyContainerPrefab<WorldLayer>::Parsers.registerParser("Constructor", &worldLayerPrefabInitParser);

        EntityPrefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().toString();
        EntityPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().toString();
        WorldLayerPrefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().toString();
        WorldLayerPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().toString();
    }

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {}

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {
        static SpriteSheetLoader spriteSheetLoader;
        resources.registerLoader(&spriteSheetLoader);
        
        static Json::JsonLoader jsonLoader;
        resources.registerLoader(&jsonLoader);
        
        static Json::JsonPropertyContainerPrefabLoader<Entity> entityFromJsonLoader(resources);
        static Json::JsonPropertyContainerPrefabLoader<WorldLayer> worldLayerFromJsonLoader(resources);
        resources.registerLoader(&entityFromJsonLoader);
        resources.registerLoader(&worldLayerFromJsonLoader);
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {

    }
    
    void EngineInternalPlugin::registerProperties() {
        PAX_PROPERTY_REGISTER(PAX::Behaviour)
        PAX_PROPERTY_REGISTER(PAX::NoClipControls)
        PAX_PROPERTY_REGISTER(PAX::VelocityBehaviour2D)
        PAX_PROPERTY_REGISTER(PAX::FollowEntityBehaviour)
        
        PAX_PROPERTY_REGISTER(PAX::Size)
        
        PAX_PROPERTY_REGISTER(PAX::Camera)

        PAX_PROPERTY_REGISTER(PAX::Graphics)
        PAX_PROPERTY_REGISTER(PAX::SceneGraphGraphics)
        PAX_PROPERTY_REGISTER(PAX::SpriteGraphics)
        PAX_PROPERTY_REGISTER(PAX::SpriteSheetGraphics)
        PAX_PROPERTY_REGISTER(PAX::AssetGraphics)

        PAX_PROPERTY_REGISTER(PAX::Light)
        PAX_PROPERTY_REGISTER(PAX::AmbientLight)
        PAX_PROPERTY_REGISTER(PAX::DirectionalLight)
        PAX_PROPERTY_REGISTER(PAX::PointLight)
        PAX_PROPERTY_REGISTER(PAX::SpotLight)
        
        PAX_PROPERTY_REGISTER(PAX::WorldLayerBehaviour)
    }
}