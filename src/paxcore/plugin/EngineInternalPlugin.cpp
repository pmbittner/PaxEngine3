//
// Created by Paul on 13.08.2018.
//

#include <paxcore/plugin/EngineInternalPlugin.h>

#include <polypropylene/serialisation/json/property/JsonEntityPrefabLoader.h>
#include <paxutil/property/construction/json/parsers/JsonEntityPrefabTransformationParser.h>

#include <paxcore/world/prefab/JsonWorldPrefabInitParser.h>
#include <paxcore/world/prefab/JsonWorldGameEntityParser.h>

#include <paxcore/gameentity/property/Behaviour.h>
#include <paxcore/gameentity/property/Size.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>
#include <paxcore/gameentity/property/behaviours/2d/Movement2D.h>
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
#include <paxcore/animation/json/AnimationBehaviourParser.h>
#include <paxcore/animation/json/DiscreteAnimationParser.h>
#include <paxcore/io/properties/InputAbilityController.h>
#include <paxcore/animation/DiscreteAnimation.h>
#include <paxcore/rendering/animation/SpriteSheetAnimations.h>
#include <paxcore/rendering/animation/SpriteSheetAnimator.h>
#include <polypropylene/serialisation/json/JsonStdContainerConverters.h>
#include <paxcore/io/Keys.h>


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

    void EngineInternalPlugin::initialize(PAX::Engine &engine) {
        PAX_LOG(Log::Level::Info, "PAX_CXX_STANDARD = " << PAX_CXX_STANDARD);
    }

    void EngineInternalPlugin::postInitialize(PAX::Engine &engine) {
        /// Parsers for GameEntityPrefab things
        static Json::JsonEntityPrefabTransformationParser<GameEntity> transformationParser;
        static JsonGameEntityPrefabMotionTypeParser entityMotionTypeParser;
        static JsonGameEntityPrefabTagsParser entityTagsParser;

        /// Parsers for WorldLayerPrefab things
        static Json::JsonWorldPrefabInitParser worldLayerPrefabInitParser;
        static Json::JsonWorldGameEntityParser worldLayerPrefabGameEntityParser;

        IPrefab::PreDefinedVariables["EngineResourceDirectory"] = Services::GetPaths().getEngineResourceDirectory().convertedToUnix().toString();
        IPrefab::PreDefinedVariables["EngineResourceDir"] = IPrefab::PreDefinedVariables["EngineResourceDirectory"];
        IPrefab::PreDefinedVariables["ERD"] = IPrefab::PreDefinedVariables["EngineResourceDirectory"];
        IPrefab::PreDefinedVariables["CustomResourceDirectory"] = Services::GetPaths().getCustomResourceDirectory().convertedToUnix().toString();
        IPrefab::PreDefinedVariables["CustomResourceDir"] = IPrefab::PreDefinedVariables["CustomResourceDirectory"];
        IPrefab::PreDefinedVariables["CRD"] = IPrefab::PreDefinedVariables["CustomResourceDirectory"];
        IPrefab::PreDefinedVariables["WorkingDirectory"] = Services::GetPaths().getWorkingDirectory().convertedToUnix().toString();

        Json::JsonEntityPrefab<GameEntity>::initialize(Services::GetJsonWriterRegister());
        Json::JsonEntityPrefab<World>::initialize(Services::GetJsonWriterRegister());

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

        static SpriteSheetAnimationsLoader spriteSheetAnimationsLoader;
        resources.registerLoader(&spriteSheetAnimationsLoader);
    }

    void EngineInternalPlugin::registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) {
        jsonTextureParser.registerAt(writerRegister);
        jsonSpriteSheetAnimationsParser.registerAt(writerRegister);

#define PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(...) \
    { \
        static Json::JsonFieldWriter<__VA_ARGS__> parser; \
        writerRegister.registerWriter(paxtypeid(__VA_ARGS__), &parser); \
    }

        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec2)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec3)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::vec4)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec2)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec3)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(glm::ivec4)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(Viewport*)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(Projection*)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(AnimationBehaviour)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(DiscreteAnimation<glm::ivec2>)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(Key)
        PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE(InputAbilityController::KeyBindings)

#undef PAX_ENGINEINTERNALPLUGIN_REGISTERPRIMITIVE
    }

    void EngineInternalPlugin::registerServices(PAX::Services &services) {

    }
    
    void EngineInternalPlugin::registerProperties() {
        PAX_PROPERTY_REGISTER(Behaviour);
        PAX_PROPERTY_REGISTER(NoClipControls);
        PAX_PROPERTY_REGISTER(Movement2D);
        PAX_PROPERTY_REGISTER(FollowGameEntityBehaviour);

        PAX_PROPERTY_REGISTER(InputAbilityController);
        
        PAX_PROPERTY_REGISTER(Size);
        
        PAX_PROPERTY_REGISTER(Camera);

        PAX_PROPERTY_REGISTER(Graphics);
        PAX_PROPERTY_REGISTER(SceneGraphGraphics);
        PAX_PROPERTY_REGISTER(SpriteGraphics);
        PAX_PROPERTY_REGISTER(SpriteSheetGraphics);
        PAX_PROPERTY_REGISTER(SpriteSheetAnimator);
        PAX_PROPERTY_REGISTER(AssetGraphics);

        PAX_PROPERTY_REGISTER(Light);
        PAX_PROPERTY_REGISTER(AmbientLight);
        PAX_PROPERTY_REGISTER(DirectionalLight);
        PAX_PROPERTY_REGISTER(PointLight);
        PAX_PROPERTY_REGISTER(SpotLight);
        
        PAX_PROPERTY_REGISTER(WorldBehaviour);
        PAX_PROPERTY_REGISTER(WorldSize);
    }
}