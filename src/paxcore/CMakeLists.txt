set(HEADERS_FOR_CLION
        ../../include/paxcore/Engine.h
        ../../include/paxcore/Game.h
        ../../include/paxcore/io/InputSystem.h

        ../../include/paxcore/entity/Entity.h
        ../../include/paxcore/entity/EntityComponent.h

        ../../include/paxcore/system/EngineSystem.h
        ../../include/paxcore/system/EntityComponentSystem.h

        ../../include/paxcore/io/Keyboard.h
        ../../include/paxcore/io/Mouse.h

        ../../include/paxcore/rendering/interface/Renderable.h
        ../../include/paxcore/rendering/Renderer.h
        ../../include/paxcore/rendering/Graphics.h

        ../../include/paxcore/rendering/data/Shader.h

        ../../include/paxcore/rendering/scenegraph/SceneGraphGenerator.h
        ../../include/paxcore/rendering/scenegraph/sort/GraphicsSort.h

        ../../include/paxcore/world/World.h
        ../../include/paxcore/world/WorldLayer.h
        ../../include/paxcore/world/WorldLayerLayout.h

        ../../include/paxutil/event/Event.h
        ../../include/paxutil/event/EventService.h
        ../../include/paxcore/entity/event/EntityEvent.h
        ../../include/paxcore/world/event/EntitySpawnedEvent.h
        ../../include/paxcore/world/event/EntityDespawnedEvent.h
        ../../include/paxcore/entity/event/EntityComponentAddedEvent.h
        ../../include/paxcore/entity/event/EntityComponentEvent.h
        ../../include/paxcore/entity/event/EntityComponentRemovedEvent.h
        ../../include/paxcore/io/Window.h
        ../../include/paxcore/rendering/camera/Camera.h
        ../../include/paxutil/event/Delegate.h
        ../../include/paxutil/event/EventHandler.h
        ../../include/paxcore/entity/event/EntityParentChangedEvent.h
        ../../include/paxcore/system/BehaviourSystem.h
        ../../include/paxcore/entity/component/Behaviour.h

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
        ../../include/paxcore/rendering/RenderFactory.h
        ../../include/paxcore/rendering/camera/FullPixelScreenProjection.h
        ../../include/paxcore/io/event/ResolutionChangedEvent.h
        ../../include/paxcore/io/resources/Resources.h
        ../../include/paxcore/io/resources/ResourceLoader.h
        ../../include/paxcore/io/resources/ResourceHandle.h
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
        ../../include/paxcore/entity/component/behaviours/NoClipControls.h
        ../../include/paxcore/io/event/MouseMovedEvent.h
        ../../include/paxcore/animation/Animation.h
        ../../include/paxcore/rendering/data/SpriteSheet.h
        ../../include/paxcore/rendering/scenegraph/nodes/TransformationNode.h
        ../../include/paxutil/io/Path.h
        ../../include/paxcore/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h
        ../../include/paxcore/world/scenegraph/WorldLayerSceneGraph.h
        ../../include/paxcore/world/scenegraph/WorldSceneGraph.h
        ../../include/paxcore/rendering/graphics/SpriteSheetGraphics.h
        ../../include/paxcore/rendering/graphics/SpriteGraphics.h
        ../../include/paxcore/rendering/interface/Shaded.h
        ../../include/paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h
        ../../include/paxcore/entity/component/Size.h
        ../../include/paxcore/entity/event/SizeChangedEvent.h
        ../../include/paxcore/entity/event/ScaleChangedEvent.h
        ../../include/paxcore/EnginePlugin.h
        ../../include/paxcore/service/Factory.h
        ../../include/paxcore/service/FactoryService.h
        ../../include/paxutil/lib/GlmIncludes.h
        ../../include/paxcore/rendering/data/Asset.h
        ../../include/paxcore/rendering/data/SkeletalMesh.h
        ../../include/paxcore/rendering/graphics/AssetGraphics.h
        ../../include/paxcore/rendering/data/Material.h
        ../../include/paxcore/rendering/light/Light.h
        ../../include/paxcore/rendering/light/PointLight.h
        ../../include/paxcore/rendering/light/DirectionalLight.h
        ../../include/paxcore/rendering/light/SpotLight.h
        ../../include/paxcore/rendering/interface/ShaderFlagsConfigurator.h)

set(CORE_SOURCE_FILES
        Engine.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        entity/Entity.cpp
        entity/EntityComponent.cpp
        entity/component/behaviours/NoClipControls.cpp
        entity/component/Behaviour.cpp
        entity/component/Size.cpp

        world/World.cpp
        world/WorldLayer.cpp
        world/scenegraph/WorldSceneGraph.cpp
        world/scenegraph/WorldLayerSceneGraph.cpp

        ../paxutil/event/EventService.cpp

        system/BehaviourSystem.cpp
        system/EntityComponentSystem.cpp


        time/Time.cpp

        generated/EngineInternalPlugin.cpp
        generated/EngineInternalPlugin.generated.cpp
        EnginePlugin.cpp)

add_subdirectory(io)
add_subdirectory(rendering)

### PRECOMPILING ########################################
find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${PROJECT_SOURCE_DIR}/precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX ${PROJECT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp EngineInternalPlugin paxcore/generated/EngineInternalPlugin.h
        COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
        DEPENDS ${PROJECT_SOURCE_DIR}/include/
        VERBATIM
)

add_library(paxcore ${HEADERS_FOR_CLION} ${CORE_SOURCE_FILES})
target_link_libraries(paxcore paxrendering paxio paxutil)