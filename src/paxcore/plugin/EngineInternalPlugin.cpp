//
// Created by Paul on 13.08.2018.
//

#include <paxcore/plugin/EngineInternalPlugin.h>

#include <paxutil/resources/Resources.h>
#include <paxutil/property/construction/json/JsonPropertyContainerPrefabLoader.h>
#include <paxutil/property/construction/json/parsers/JsonPropertyContainerPrefabTransformationParser.h>

#include <paxcore/world/prefab/JsonWorldLayerPrefabInitParser.h>
#include <paxcore/world/prefab/JsonWorldLayerEntityParser.h>
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
#include <paxcore/world/property/WorldLayerSize.h>

namespace PAX {
    // TODO: Find a way for easier and better custom json element parsing integration.
    class JsonEntityPrefabTransformationMotionType : public Json::JsonPropertyContainerPrefabElementParser<Entity> {
    public:
        void parse(nlohmann::json & node, Entity & e, Json::JsonPropertyContainerPrefab<Entity> & prefab, const VariableRegister & v) override {
            MotionType motionType = MotionType::Static;
            std::string motionTypeString = JsonToString(node);

            if (motionTypeString == "Dynamic") {
                motionType = MotionType::Dynamic;
            } else if (motionTypeString == "Kinematic") {
                motionType = MotionType::Kinematic;
            } else if (motionTypeString != "Static") {
                PAX_THROW_RUNTIME_ERROR("Unknown MotionType given: " << motionTypeString);
            }

            e.i_setMotionType(motionType);
        }
    };

    void EngineInternalPlugin::initialize(PAX::Engine &engine) {}

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        static Json::JsonPropertyContainerPrefabTransformationParser<Entity> transformationParser;
        static Json::JsonWorldLayerPrefabInitParser worldLayerPrefabInitParser;
        static Json::JsonWorldLayerEntityParser worldLayerPrefabEntityParser;
        static JsonEntityPrefabTransformationMotionType entityMotionTypeParser;

        Json::JsonPropertyContainerPrefab<Entity>::initialize(Services::GetResources());
        Json::JsonPropertyContainerPrefab<WorldLayer>::initialize(Services::GetResources());

        Json::JsonPropertyContainerPrefab<Entity>::Parsers.registerParser("Transform", &transformationParser);
        Json::JsonPropertyContainerPrefab<Entity>::Parsers.registerParser("MotionType", &entityMotionTypeParser);
        Json::JsonPropertyContainerPrefab<WorldLayer>::Parsers.registerParser("Constructor", &worldLayerPrefabInitParser);
        Json::JsonPropertyContainerPrefab<WorldLayer>::Parsers.registerParser("Entities", &worldLayerPrefabEntityParser);

        Prefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().convertedToUnix().toString();
        Prefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().convertedToUnix().toString();

        /// If no texture loaders have been registered, register the null texture loader.
        // FIXME: Is there maybe a better place for this?
        if (Services::GetResources().getLoaders<Texture>().empty()) {
            Services::GetResources().registerLoader(&nullTextureLoader);
        }
    }

    void EngineInternalPlugin::registerFactories(PAX::FactoryService &factoryService) {
        factoryService.set(paxtypeid(SceneGraphGeneratorFactory), &defaultSceneGraphGeneratorFactory);
    }

    void EngineInternalPlugin::registerResourceLoaders(PAX::Resources &resources) {
        resources.registerLoader(&spriteSheetLoader);
        resources.registerLoader(&jsonLoader);

        // FIXME:? Can we make these independent from the resources object?
        static Json::JsonPropertyContainerPrefabLoader<Entity>     entityFromJsonLoader(resources);
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
        PAX_PROPERTY_REGISTER(PAX::WorldLayerSize)
    }
}