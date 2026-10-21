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
        gameentity/property/Ability.cpp
        animation/Timing.cpp
        system/gameentity/GameEntityPropertyPool.cpp
        animation/json/AnimationBehaviourParser.cpp
        animation/AnimationBehaviour.cpp)

add_subdirectory(io)
add_subdirectory(rendering)

add_library(paxcore ${CORE_SOURCE_FILES})
add_library(PaxEngine3::paxcore ALIAS paxcore)
# paxcore, paxrendering, and paxio reference each other, which is fine for static libraries.
target_link_libraries(paxcore PUBLIC paxutil paxio paxrendering)
