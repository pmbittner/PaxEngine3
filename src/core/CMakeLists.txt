set(CORE_SOURCE_FILES
        Engine.cpp
        EngineSetup.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        entity/Entity.cpp
        entity/EntityComponent.cpp
        entity/Transform.cpp

        io/Keyboard.cpp
        io/Mouse.cpp
        io/Window.cpp
        io/event/ResolutionChangedEvent.cpp
        io/resources/ResourceHandle.cpp

        rendering/Renderer.cpp
        rendering/Viewport.cpp
        rendering/scenegraph/nodes/TexturingNode.cpp
        rendering/Graphics.cpp
        rendering/RenderOptions.cpp

        rendering/camera/Camera.cpp
        rendering/camera/Projection.cpp
        rendering/camera/PerspectiveProjection.cpp
        rendering/camera/PixelScreenProjection.cpp
        rendering/camera/FullPixelScreenProjection.cpp

        rendering/scenegraph/SceneGraphGenerator.cpp
        rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.cpp
        rendering/scenegraph/nodes/SortingNode.cpp
        rendering/scenegraph/nodes/ShadingNode.cpp
        rendering/scenegraph/sort/GraphicsSort.cpp

        rendering/resource/Mesh.cpp
        rendering/resource/Shader.cpp
        rendering/resource/Texture.cpp

        world/World.cpp
        world/WorldLayer.cpp

        event/EventService.cpp

        system/BehaviourSystem.cpp
        system/EntityComponentSystem.cpp

        time/Time.cpp rendering/scenegraph/nodes/MeshNode.cpp rendering/SceneGraphGraphics.cpp)

add_library(paxcore ${CORE_SOURCE_FILES})
target_link_libraries(paxcore)