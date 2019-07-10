set(HEADERS_FOR_CLION
        ../../include/paxcore/Engine.h
        ../../include/paxcore/Game.h
        ../../include/paxcore/io/InputSystem.h

        ../../include/paxcore/entity/Entity.h
        ../../include/paxcore/entity/EntityProperty.h

        ../../include/paxcore/system/EngineSystem.h

        ../../include/paxcore/io/Keyboard.h
        ../../include/paxcore/io/Mouse.h

        ../../include/paxcore/rendering/interface/Renderable.h
        ../../include/paxcore/rendering/Renderer.h
        ../../include/paxcore/rendering/Graphics.h

        ../../include/paxcore/rendering/data/Shader.h

        ../../include/paxcore/rendering/scenegraph/generators/SceneGraphGenerator.h
        ../../include/paxcore/rendering/scenegraph/sort/GraphicsSort.h

        ../../include/paxcore/world/World.h
        ../../include/paxcore/world/WorldLayer.h
        ../../include/paxcore/world/WorldLayerLayout.h

        ../../include/paxcore/entity/event/EntityEvent.h
        ../../include/paxcore/world/event/EntitySpawnedEvent.h
        ../../include/paxcore/world/event/EntityDespawnedEvent.h
        ../../include/paxcore/io/Window.h
        ../../include/paxcore/rendering/camera/Camera.h
        ../../include/paxcore/entity/event/EntityParentChangedEvent.h
        ../../include/paxcore/system/entity/BehaviourSystem.h
        ../../include/paxcore/entity/property/Behaviour.h

        ../../include/paxcore/io/event/MouseButtonPressedEvent.h
        ../../include/paxcore/io/event/MouseButtonReleasedEvent.h
        ../../include/paxcore/io/event/MouseButtonEvent.h
        ../../include/paxcore/time/Time.h
        ../../include/paxcore/rendering/Viewport.h
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
        ../../include/paxcore/rendering/data/CPUMesh.h
        ../../include/paxcore/io/event/KeyEvent.h
        ../../include/paxcore/io/event/KeyPressedEvent.h
        ../../include/paxcore/io/event/KeyReleasedEvent.h
        ../../include/paxcore/io/MouseButtons.h
        ../../include/paxcore/io/event/MouseWheelEvent.h
        ../../include/paxcore/io/event/MouseEvent.h
        ../../include/paxcore/service/Paths.h
        ../../include/paxcore/rendering/scenegraph/nodes/MeshNode.h
        ../../include/paxcore/rendering/graphics/SceneGraphGraphics.h
        ../../include/paxcore/entity/property/behaviours/NoClipControls.h
        ../../include/paxcore/io/event/MouseMovedEvent.h
        ../../include/paxcore/animation/Animation.h
        ../../include/paxcore/rendering/data/SpriteSheet.h
        ../../include/paxcore/rendering/scenegraph/nodes/TransformationNode.h
        ../../include/paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h
        ../../include/paxcore/world/scenegraph/WorldLayerSceneGraph.h
        ../../include/paxcore/world/scenegraph/WorldSceneGraph.h
        ../../include/paxcore/rendering/graphics/SpriteSheetGraphics.h
        ../../include/paxcore/rendering/graphics/SpriteGraphics.h
        ../../include/paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h
        ../../include/paxcore/entity/property/behaviours/2d/VelocityBehaviour2D.h
        ../../include/paxcore/entity/property/Size.h
        ../../include/paxcore/entity/event/SizeChangedEvent.h
        ../../include/paxcore/entity/event/ScaleChangedEvent.h
        ../../include/paxcore/plugin/EnginePlugin.h
        ../../include/paxcore/service/FactoryService.h
        ../../include/paxcore/rendering/data/Asset.h
        ../../include/paxcore/rendering/graphics/AssetGraphics.h
        ../../include/paxcore/rendering/data/Material.h
        ../../include/paxcore/rendering/light/Light.h
        ../../include/paxcore/rendering/light/PointLight.h
        ../../include/paxcore/rendering/light/DirectionalLight.h
        ../../include/paxcore/rendering/light/SpotLight.h
        ../../include/paxcore/rendering/interface/ShaderFlagsConfigurator.h
        ../../include/paxcore/world/WorldLayerProperty.h
        ../../include/paxcore/system/worldlayer/WorldLayerPropertySystem.h
        ../../include/paxcore/rendering/light/AmbientLight.h
        ../../include/paxcore/system/entity/LightSystem.h
        ../../include/paxcore/service/WindowService.h
        ../../include/paxcore/rendering/renderpass/RenderPass.h
        ../../include/paxcore/rendering/loader/SpriteSheetLoader.h
        ../../include/paxcore/rendering/factory/MeshFactory.h
        ../../include/paxcore/rendering/factory/ViewportFactory.h
        ../../include/paxcore/io/InputSystemFactory.h
        ../../include/paxcore/world/scenegraph/WorldLayerSceneGraphFactory.h
        ../../include/paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h
        ../../include/paxcore/io/WindowFactory.h
        ../../include/paxcore/system/worldlayer/WorldLayerBehaviourSystem.h
        ../../include/paxcore/system/entity/EntityPropertySystem.h
        ../../include/paxcore/system/WorldSystem.h
        ../../include/paxcore/world/property/WorldLayerBehaviour.h
        ../../include/paxcore/world/prefab/JsonWorldLayerPrefabInitParser.h
        ../../include/paxcore/rendering/renderpass/RenderPassChannel.h
        ../../include/paxcore/rendering/renderpass/RenderPassFactory.h
        ../../include/paxcore/entity/property/behaviours/2d/FollowEntityBehaviour.h
        ../../include/paxcore/world/property/WorldLayerSize.h
        ../../include/paxcore/entity/EntityIDService.h
        ../../include/paxcore/world/prefab/JsonWorldLayerEntityParser.h ../../include/paxcore/rendering/scenegraph/generators/DefaultSceneGraphGeneratorFactory.h)

set(CORE_SOURCE_FILES
        Engine.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        entity/Entity.cpp
        entity/EntityProperty.cpp
        entity/property/Behaviour.cpp
        entity/property/Size.cpp
        entity/property/behaviours/NoClipControls.cpp
        entity/property/behaviours/2d/VelocityBehaviour2D.cpp
        entity/property/behaviours/2d/FollowEntityBehaviour.cpp

        world/World.cpp
        world/WorldLayer.cpp
        world/scenegraph/WorldSceneGraph.cpp
        world/scenegraph/WorldLayerSceneGraph.cpp

        system/entity/BehaviourSystem.cpp

        time/Time.cpp

        plugin/EngineInternalPlugin.cpp
        plugin/EnginePlugin.cpp
        system/entity/LightSystem.cpp
        service/WindowService.cpp
        system/WorldSystem.cpp
        system/worldlayer/WorldLayerBehaviourSystem.cpp
        world/prefab/JsonWorldLayerPrefabInitParser.cpp
        world/property/WorldLayerSize.cpp
        world/property/WorldLayerBehaviour.cpp
        entity/EntityIDService.cpp world/prefab/JsonWorldLayerEntityParser.cpp)

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
target_link_libraries(paxcore paxrendering paxio paxutil)