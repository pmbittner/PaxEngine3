//
// Created by Paul on 13.08.2018.
//

#include <paxcore/plugin/EngineInternalPlugin.h>

#include <paxutil/resources/Resources.h>
#include <polypropylene/serialisation/json/property/JsonEntityPrefabLoader.h>
#include <paxutil/property/construction/json/parsers/JsonEntityPrefabTransformationParser.h>

#include <paxcore/world/prefab/JsonWorldPrefabInitParser.h>
#include <paxcore/world/prefab/JsonWorldGameEntityParser.h>
#include <paxcore/service/Services.h>

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/gameentity/property/Size.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>
#include <paxcore/gameentity/property/behaviours/2d/VelocityBehaviour2D.h>
#include <paxcore/gameentity/property/behaviours/2d/FollowGameEntityBehaviour.h>
#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/rendering/graphics/SpriteSheetGraphics.h>
#include <paxcore/rendering/light/AmbientLight.h>
#include <paxcore/rendering/light/DirectionalLight.h>
#include <paxcore/rendering/light/SpotLight.h>
#include <paxcore/rendering/light/PointLight.h>
#include <paxcore/world/property/WorldBehaviour.h>
#include <paxcore/world/property/WorldSize.h>
#include <paxcore/gameentity/prefab/JsonGameEntityPrefabTagsParser.h>
#include <paxcore/json/JsonEntityPrefabResourceLoader.h>

// Do not remove although propably marked as unnecessary because we have template specialisations in here that
// won't be recognised if not included.
#include <paxcore/rendering/camera/json/ViewportJsonParser.h>
#include <paxcore/rendering/camera/json/ProjectionJsonParser.h>

namespace PAX {
    // TODO: Find a way for easier and better custom json element parsing integration.
    class JsonGameEntityPrefabMotionTypeParser : public Json::JsonEntityPrefabElementParser<GameEntity> {
    public:
        void parse(nlohmann::json & node, GameEntity & e, Json::JsonEntityPrefab<GameEntity> & prefab, const VariableRegister & v) override {
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
        /// Parsers for GameEntityPrefab things
        static Json::JsonEntityPrefabTransformationParser<GameEntity> transformationParser;
        static JsonGameEntityPrefabMotionTypeParser entityMotionTypeParser;
        static JsonGameEntityPrefabTagsParser entityTagsParser;

        /// Parsers for WorldLayerPrefab things
        static Json::JsonWorldPrefabInitParser worldLayerPrefabInitParser;
        static Json::JsonWorldGameEntityParser worldLayerPrefabGameEntityParser;

        IPrefab::PreDefinedVariables["ResourcePath"]     = Services::GetPaths().getResourcePath().convertedToUnix().toString();
        IPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().convertedToUnix().toString();

        Json::JsonEntityPrefab<GameEntity>::initialize(Services::GetJsonParserRegister());
        Json::JsonEntityPrefab<World>::initialize(Services::GetJsonParserRegister());

        { // register parsers for GameEntityPrefab
            Json::JsonEntityPrefab<GameEntity>::ElementParsers.registerParser("Transform", &transformationParser);
            Json::JsonEntityPrefab<GameEntity>::ElementParsers.registerParser("MotionType", &entityMotionTypeParser);
            Json::JsonEntityPrefab<GameEntity>::ElementParsers.registerParser("Tags", &entityTagsParser);
            std::vector<std::string> &GEParseOrder = Json::JsonEntityPrefab<GameEntity>::ParseOrder;
            GEParseOrder.insert(GEParseOrder.begin(), "Tags");
        }

        { // register parsers for WorldPrefab
            Json::JsonEntityPrefab<World>::ElementParsers.registerParser("Constructor",
                                                                              &worldLayerPrefabInitParser);
            Json::JsonEntityPrefab<World>::ElementParsers.registerParser("Entities",
                                                                              &worldLayerPrefabGameEntityParser);
            std::vector<std::string> & WParseOrder = Json::JsonEntityPrefab<World>::ParseOrder;
            WParseOrder.insert(WParseOrder.begin(), "Constructor");
            WParseOrder.emplace_back("Entities");
        }


        /// If no texture loaders have been registered, register the null texture loader.
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

        static JsonEntityPrefabResourceLoader<GameEntity> entityFromJsonLoader;
        static JsonEntityPrefabResourceLoader<World> worldFromJsonLoader;
        resources.registerLoader(&entityFromJsonLoader);
        resources.registerLoader(&worldFromJsonLoader);
    }

    void EngineInternalPlugin::registerJsonParsers(Json::JsonParserRegister & parserRegister) {
        jsonTextureParser.registerAt(parserRegister);

#define PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(type) \
    { \
        static Json::JsonParser<type> parser; \
        parserRegister.registerParser(paxtypeid(type), &parser); \
    }

        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec2)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec3)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec4)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec2)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec3)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec4)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(Viewport*)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(Projection*)

#undef PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {

    }
    
    void EngineInternalPlugin::registerProperties() {
        PAX_PROPERTY_REGISTER(PAX::Behaviour);
        PAX_PROPERTY_REGISTER(PAX::NoClipControls);
        PAX_PROPERTY_REGISTER(PAX::VelocityBehaviour2D);
        PAX_PROPERTY_REGISTER(PAX::FollowGameEntityBehaviour);
        
        PAX_PROPERTY_REGISTER(PAX::Size);
        
        PAX_PROPERTY_REGISTER(PAX::Camera);

        PAX_PROPERTY_REGISTER(PAX::Graphics);
        PAX_PROPERTY_REGISTER(PAX::SceneGraphGraphics);
        PAX_PROPERTY_REGISTER(PAX::SpriteGraphics);
        PAX_PROPERTY_REGISTER(PAX::SpriteSheetGraphics);
        PAX_PROPERTY_REGISTER(PAX::AssetGraphics);

        PAX_PROPERTY_REGISTER(PAX::Light);
        PAX_PROPERTY_REGISTER(PAX::AmbientLight);
        PAX_PROPERTY_REGISTER(PAX::DirectionalLight);
        PAX_PROPERTY_REGISTER(PAX::PointLight);
        PAX_PROPERTY_REGISTER(PAX::SpotLight);
        
        PAX_PROPERTY_REGISTER(PAX::WorldBehaviour);
        PAX_PROPERTY_REGISTER(PAX::WorldSize);
    }
}