set(HEADERS_FOR_CLION
        ../../include/core/Engine.h
        ../../include/core/Game.h
        ../../include/core/io/InputSystem.h

        ../../include/core/entity/Entity.h
        ../../include/core/entity/EntityComponent.h
        ../../include/core/entity/component/allocators/EntityComponentPool.h
        ../../include/core/entity/Transform.h

        ../../include/core/system/EngineSystem.h
        ../../include/core/system/EntityComponentSystem.h

        ../../include/core/io/Keyboard.h
        ../../include/core/io/Mouse.h

        ../../include/core/rendering/interface/Renderable.h
        ../../include/core/rendering/Renderer.h
        ../../include/core/rendering/Graphics.h

        ../../include/core/rendering/resource/Shader.h

        ../../include/core/rendering/scenegraph/SceneGraphGenerator.h
        ../../include/core/rendering/scenegraph/sort/GraphicsSort.h

        ../../include/core/world/World.h
        ../../include/core/world/WorldLayer.h
        ../../include/core/world/WorldLayerLayout.h

        ../../include/core/event/Event.h
        ../../include/core/event/EventService.h
        ../../include/core/entity/event/EntityEvent.h
        ../../include/core/world/event/EntitySpawnedEvent.h
        ../../include/core/world/event/EntityDespawnedEvent.h
        ../../include/core/event/EventListener.h
        ../../include/core/entity/EntityComponentAllocator.h
        ../../include/core/entity/event/EntityComponentAddedEvent.h
        ../../include/core/entity/event/EntityComponentEvent.h
        ../../include/core/entity/event/EntityComponentRemovedEvent.h
        ../../include/core/io/Window.h
        ../../include/core/rendering/camera/Camera.h
        ../../include/core/event/Delegate.h
        ../../include/core/event/EventHandler.h
        ../../include/core/entity/event/EntityParentChangedEvent.h
        ../../include/core/system/BehaviourSystem.h
        ../../include/core/entity/component/Behaviour.h

        ../../include/core/io/event/MouseButtonPressedEvent.h
        ../../include/core/io/event/MouseButtonReleasedEvent.h
        ../../include/core/io/event/MouseButtonEvent.h
        ../../include/core/time/Time.h
        ../../include/core/rendering/Viewport.h
        ../../include/core/rendering/graphics/nodes/TexturingNode.h
        ../../include/core/rendering/resource/Mesh.h
        ../../include/core/rendering/resource/Texture.h
        ../../include/core/rendering/camera/Projection.h
        ../../include/core/rendering/camera/PerspectiveProjection.h
        ../../include/core/rendering/RenderOptions.h
        ../../include/core/rendering/RenderFactory.h
        ../../include/core/rendering/camera/FullPixelScreenProjection.h
        ../../include/core/io/event/ResolutionChangedEvent.h
        ../../include/core/entity/EntityComponentDependency.h
        ../../include/core/io/resources/Resources.h
        ../../include/core/io/resources/ResourceLoader.h
        ../../include/core/io/resources/ResourceHandle.h
        ../../include/core/service/Services.h
        ../../include/core/rendering/scenegraph/nodes/SortingNode.h
        ../../include/core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h
        ../../include/core/rendering/event/ShaderChangedEvent.h
        ../../include/core/rendering/scenegraph/nodes/ShadingNode.h
        ../../include/core/rendering/event/GraphicsShaderChangedEvent.h
        ../../include/core/rendering/scenegraph/SceneGraph.h
        ../../include/core/rendering/data/CPUMesh.h
        ../../include/core/entity/component/allocators/EntityComponentMallocAllocator.h
        ../../include/core/entity/EntityComponentService.h
        ../../include/core/io/event/KeyEvent.h
        ../../include/core/io/event/KeyPressedEvent.h
        ../../include/core/io/event/KeyReleasedEvent.h
        ../../include/core/io/MouseButtons.h
        ../../include/core/io/event/MouseWheelEvent.h
        ../../include/core/io/event/MouseEvent.h
        ../../include/core/service/Paths.h
        ../../include/core/rendering/graphics/nodes/MeshNode.h
        ../../include/core/rendering/graphics/SceneGraphGraphics.h
        ../../include/core/entity/component/behaviours/NoClipControls.h
        ../../include/core/io/event/MouseMovedEvent.h
        ../../include/core/animation/Animation.h
        ../../include/core/rendering/resource/SpriteSheet.h
        ../../include/core/rendering/scenegraph/nodes/TransformationNode.h
        ../../include/core/io/resources/Path.h
        ../../include/core/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h
        ../../include/core/world/scenegraph/WorldLayerSceneGraph.h
        ../../include/core/world/scenegraph/WorldSceneGraph.h
        ../../include/core/rendering/graphics/SpriteSheetGraphics.h
        ../../include/core/rendering/graphics/SpriteGraphics.h
        ../../include/core/rendering/resource/Shaded.h
        ../../include/core/rendering/graphics/nodes/SpriteSheetNode.h
        ../../include/core/entity/component/Size.h
        ../../include/core/entity/event/SizeChangedEvent.h
        ../../include/core/entity/event/ScaleChangedEvent.h
        ../../include/core/EnginePlugin.h
        ../../include/core/service/Factory.h
        ../../include/core/reflection/EntityComponentReflectionData.h
        ../../include/core/service/FactoryService.h
        ../../include/utility/lib/GlmIncludes.h
        )

set(CORE_SOURCE_FILES
        Engine.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        entity/Entity.cpp
        entity/EntityComponent.cpp
        entity/Transform.cpp
        entity/component/behaviours/NoClipControls.cpp
        entity/component/Behaviour.cpp
        entity/component/Size.cpp

        world/World.cpp
        world/WorldLayer.cpp
        world/scenegraph/WorldSceneGraph.cpp
        world/scenegraph/WorldLayerSceneGraph.cpp

        event/EventService.cpp

        system/BehaviourSystem.cpp
        system/EntityComponentSystem.cpp


        time/Time.cpp

        reflection/EntityComponentReflectionData.cpp

        generated/EngineInternalPlugin.cpp
        generated/EngineInternalPlugin.generated.cpp EnginePlugin.cpp)

add_subdirectory(io)
add_subdirectory(rendering)

### PRECOMPILING ########################################
find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${PROJECT_SOURCE_DIR}/precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX ${PROJECT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/generated/EngineInternalPlugin.generated.cpp EngineInternalPlugin core/generated/EngineInternalPlugin.h
        COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
        DEPENDS ${PROJECT_SOURCE_DIR}/include/
        VERBATIM
)

add_library(paxcore ${HEADERS_FOR_CLION} ${CORE_SOURCE_FILES})
target_link_libraries(paxcore paxrendering paxio paxutil)