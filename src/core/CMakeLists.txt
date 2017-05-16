set(CORE_SOURCE_FILES
        Engine.cpp
        Game.cpp

        entity/Entity.cpp
        entity/EntityComponent.cpp
        entity/Transform.cpp

        io/Keyboard.cpp
        io/Mouse.cpp

        rendering/Renderer.cpp
        rendering/scenegraph/sort/RenderableSort.cpp
        rendering/scenegraph/SceneGraph.cpp
        rendering/scenegraph/SceneGraphBuilder.cpp

        world/World.cpp
        world/WorldLayer.cpp
        rendering/Camera.cpp)

add_library(paxcore ${CORE_SOURCE_FILES})
target_link_libraries(paxcore)