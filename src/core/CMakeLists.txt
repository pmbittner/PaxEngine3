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
        generated/EngineInternalPlugin.generated.cpp)

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

add_library(paxcore ${CORE_SOURCE_FILES})
target_link_libraries(paxcore paxrendering paxio paxutil)