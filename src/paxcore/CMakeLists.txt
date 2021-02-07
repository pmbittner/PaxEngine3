set(HEADERS_FOR_CLION
        ../../include/paxcore/Engine.h
        ../../include/paxcore/Game.h
        ../../include/paxcore/io/InputSystem.h

        ../../include/paxcore/gameentity/GameEntity.h
        ../../include/paxcore/gameentity/GameEntityProperty.h

        ../../include/paxcore/io/Keyboard.h
        ../../include/paxcore/io/Mouse.h

        ../../include/paxcore/rendering/interface/Renderable.h
        ../../include/paxcore/rendering/Renderer.h
        ../../include/paxcore/rendering/Graphics.h

        ../../include/paxcore/rendering/data/Shader.h

        ../../include/paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h
        ../../include/paxcore/rendering/scenegraph/sort/GraphicsSort.h

        ../../include/paxcore/world/World.h

        ../../include/paxcore/gameentity/event/GameEntityEvent.h
        ../../include/paxcore/world/event/GameEntitySpawnedEvent.h
        ../../include/paxcore/world/event/GameEntityDespawnedEvent.h
        ../../include/paxcore/io/Window.h
        ../../include/paxcore/rendering/camera/Camera.h
        ../../include/paxcore/gameentity/event/GameEntityParentChangedEvent.h
        ../../include/paxcore/system/gameentity/BehaviourSystem.h
        ../../include/paxcore/gameentity/property/Behaviour.h

        ../../include/paxcore/io/event/MouseButtonPressedEvent.h
        ../../include/paxcore/io/event/MouseButtonReleasedEvent.h
        ../../include/paxcore/io/event/MouseButtonEvent.h
        ../../include/paxcore/function/Updateable.h
        ../../include/paxcore/function/UpdateOptions.h
        ../../include/paxcore/rendering/camera/Viewport.h
        ../../include/paxcore/rendering/scenegraph/nodes/TexturingNode.h
        ../../include/paxcore/rendering/data/Mesh.h
        ../../include/paxcore/rendering/data/Texture.h
        ../../include/paxcore/rendering/camera/Projection.h
        ../../include/paxcore/rendering/camera/PerspectiveProjection.h
        ../../include/paxcore/rendering/RenderOptions.h
        ../../include/paxcore/rendering/camera/FullPixelScreenProjection.h
        ../../include/paxcore/io/event/ResolutionChangedEvent.h
        ../../include/paxcore/service/Services.h
        ../../include/paxcore/rendering/scenegraph/nodes/SortingNode.h
        ../../include/paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h
        ../../include/paxcore/rendering/event/ShaderChangedEvent.h
        ../../include/paxcore/rendering/scenegraph/nodes/ShadingNode.h
        ../../include/paxcore/rendering/event/GraphicsShaderChangedEvent.h
        ../../include/paxcore/rendering/scenegraph/SceneGraph.h
        ../../include/paxcore/io/event/KeyEvent.h
        ../../include/paxcore/io/event/KeyPressedEvent.h
        ../../include/paxcore/io/event/KeyReleasedEvent.h
        ../../include/paxcore/io/MouseButtons.h
        ../../include/paxcore/io/event/MouseWheelEvent.h
        ../../include/paxcore/io/event/MouseEvent.h
        ../../include/paxcore/service/Paths.h
        ../../include/paxcore/rendering/scenegraph/nodes/MeshNode.h
        ../../include/paxcore/rendering/graphics/SceneGraphGraphics.h
        ../../include/paxcore/gameentity/property/behaviours/NoClipControls.h
        ../../include/paxcore/io/event/MouseMovedEvent.h
        ../../include/paxcore/animation/Animation.h
        ../../include/paxcore/rendering/data/SpriteSheet.h
        ../../include/paxcore/rendering/scenegraph/nodes/TransformationNode.h
        ../../include/paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h
        ../../include/paxcore/world/scenegraph/WorldSceneGraph.h
        ../../include/paxcore/rendering/graphics/SpriteSheetGraphics.h
        ../../include/paxcore/rendering/graphics/SpriteGraphics.h
        ../../include/paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h
        ../../include/paxcore/gameentity/property/behaviours/2d/Movement2D.h
        ../../include/paxcore/gameentity/property/Size.h
        ../../include/paxcore/gameentity/event/SizeChangedEvent.h
        ../../include/paxcore/gameentity/event/ScaleChangedEvent.h
        ../../include/paxcore/plugin/EnginePlugin.h
        ../../include/paxcore/service/FactoryService.h
        ../../include/paxcore/rendering/data/Asset.h
        ../../include/paxcore/rendering/graphics/AssetGraphics.h
        ../../include/paxcore/rendering/data/Material.h
        ../../include/paxcore/rendering/light/Light.h
        ../../include/paxcore/rendering/light/PointLight.h
        ../../include/paxcore/rendering/light/DirectionalLight.h
        ../../include/paxcore/rendering/light/SpotLight.h
        ../../include/paxcore/world/WorldProperty.h
        ../../include/paxcore/rendering/light/AmbientLight.h
        ../../include/paxcore/system/gameentity/LightSystem.h
        ../../include/paxcore/service/WindowService.h
        ../../include/paxcore/rendering/renderpass/RenderPass.h
        ../../include/paxcore/rendering/loader/SpriteSheetLoader.h
        ../../include/paxcore/rendering/loader/NullTextureLoader.h
        ../../include/paxcore/rendering/factory/MeshFactory.h
        ../../include/paxcore/rendering/factory/ViewportFactory.h
        ../../include/paxcore/io/InputSystemFactory.h
        ../../include/paxcore/world/scenegraph/WorldSceneGraphFactory.h
        ../../include/paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h
        ../../include/paxcore/io/WindowFactory.h
        ../../include/paxcore/system/world/WorldBehaviourSystem.h
        ../../include/paxcore/system/gameentity/GameEntityPropertySystem.h
        ../../include/paxcore/world/property/WorldBehaviour.h
        ../../include/paxcore/world/prefab/JsonWorldPrefabInitParser.h
        ../../include/paxcore/rendering/renderpass/RenderPassChannel.h
        ../../include/paxcore/rendering/renderpass/RenderPassFactory.h
        ../../include/paxcore/gameentity/property/behaviours/2d/FollowGameEntityBehaviour.h
        ../../include/paxcore/world/property/WorldSize.h
        ../../include/paxcore/gameentity/GameEntityIDService.h
        ../../include/paxcore/world/prefab/JsonWorldGameEntityParser.h
        ../../include/paxcore/rendering/scenegraph/generators/DefaultSceneGraphGeneratorFactory.h
        ../../include/paxcore/rendering/factory/TextureFactory.h
        ../../include/paxcore/gameentity/MotionType.h
        ../../include/paxcore/gameentity/Tag.h
        ../../include/paxcore/gameentity/prefab/JsonGameEntityPrefabTagsParser.h
        ../../include/paxcore/json/JsonResourceLoader.h
        ../../include/paxcore/json/JsonEntityPrefabResourceLoader.h
        ../../include/paxcore/rendering/camera/json/ViewportJsonParser.h
        ../../include/paxcore/rendering/camera/json/ProjectionJsonParser.h
        ../../include/paxcore/rendering/data/Image.h
        ../../include/paxcore/rendering/config/PointCloudSettings.h
        ../../include/paxcore/rendering/data/Colour.h
        ../../include/paxcore/rendering/data/ColourPalette.h
        ../../include/paxcore/rendering/primitives/PrimitiveFactory.h
        ../../include/paxcore/state/StateMachine.h
        ../../include/paxcore/gameentity/property/AbilityIdentifier.h
        ../../include/paxcore/gameentity/property/Ability.h
        ../../include/paxcore/io/properties/InputAbilityController.h
        ../../include/paxcore/animation/DiscreteAnimation.h ../../include/paxcore/animation/AnimationBehaviour.h ../../include/paxcore/animation/Timing.h ../../include/paxcore/OStreamOverloads.h ../../include/paxcore/system/gameentity/GameEntityPropertyPool.h)

set(CORE_SOURCE_FILES
        Engine.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        gameentity/GameEntity.cpp
        gameentity/property/Behaviour.cpp
        gameentity/property/Size.cpp
        gameentity/property/behaviours/NoClipControls.cpp
        gameentity/property/behaviours/2d/Movement2D.cpp
        gameentity/property/behaviours/2d/FollowGameEntityBehaviour.cpp

        world/World.cpp
        world/scenegraph/WorldSceneGraph.cpp

        system/gameentity/BehaviourSystem.cpp

        function/UpdateOptions.cpp

        plugin/EngineInternalPlugin.cpp
        plugin/EnginePlugin.cpp
        system/gameentity/LightSystem.cpp
        service/WindowService.cpp
        system/world/WorldBehaviourSystem.cpp
        world/prefab/JsonWorldPrefabInitParser.cpp
        world/property/WorldSize.cpp
        world/property/WorldBehaviour.cpp
        gameentity/GameEntityIDService.cpp
        world/prefab/JsonWorldGameEntityParser.cpp
        function/Updateable.cpp
        gameentity/prefab/JsonGameEntityPrefabTagsParser.cpp
        json/JsonResourceLoader.cpp
        gameentity/GameEntityProperty.cpp
        system/GameSystem.cpp state/StateMachine.cpp
        gameentity/property/Ability.cpp animation/Timing.cpp system/gameentity/GameEntityPropertyPool.cpp)

add_subdirectory(io)
add_subdirectory(rendering)

### PRECOMPILING ########################################
#[[
if (PAX_RUN_PYTHON_PRECOMPILER)
    find_package(PythonInterp 3 REQUIRED)
    set(SCRIPT_DIR ${PROJECT_SOURCE_DIR}/precompiler/pluginprecompiler.py)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp
            COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX ${PROJECT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp EngineInternalPlugin paxcore/generated/EngineInternalPlugin.h
            COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
            DEPENDS ${PROJECT_SOURCE_DIR}/include/
            VERBATIM
    )
    set(CORE_SOURCE_FILES ${CORE_SOURCE_FILES} generated/EngineInternalPlugin.generated.cpp)
endif(PAX_RUN_PYTHON_PRECOMPILER)
]]

add_library(paxcore ${HEADERS_FOR_CLION} ${CORE_SOURCE_FILES})
target_link_libraries(paxcore polypropylene paxrendering paxio paxutil)