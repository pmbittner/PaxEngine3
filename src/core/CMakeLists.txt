set(CORE_SOURCE_FILES
        Engine.cpp
        EngineSetup.cpp
        Game.cpp

        service/Services.cpp
        service/Paths.cpp

        entity/Entity.cpp
        entity/EntityComponent.cpp
        entity/Transform.cpp
        entity/component/behaviours/NoClipControls.cpp

        world/World.cpp
        world/WorldLayer.cpp
        world/scenegraph/WorldSceneGraph.cpp
        world/scenegraph/WorldLayerSceneGraph.cpp

        event/EventService.cpp

        system/BehaviourSystem.cpp
        system/EntityComponentSystem.cpp

        time/Time.cpp
        ../test/ResourceTest.cpp)

add_subdirectory(io)
add_subdirectory(rendering)

add_library(paxcore ${CORE_SOURCE_FILES})
target_link_libraries(paxcore paxrendering paxio paxgenerated)