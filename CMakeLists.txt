cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### FLAGS ###############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

### SOURCE FILES ########################################
set(SOURCE_FILES Default_main.cpp src/EngineMain.cpp src/lib/easylogging++.cc
        # Header files for CLion
        include/lib/easylogging++.h

        include/core/Engine.h
        include/core/Game.h
        include/core/io/InputSystem.h

        include/core/entity/Entity.h
        include/core/entity/EntityComponent.h
        include/core/entity/EntityComponentPool.h
        include/core/entity/Transform.h

        include/core/interfaces/IEngineSystem.h
        include/core/interfaces/IGameSystem.h

        include/core/io/Keyboard.h
        include/core/io/Mouse.h
        include/core/io/Screen.h

        include/core/rendering/Renderable.h
        include/core/rendering/Renderer.h
        include/core/rendering/Graphics.h

        include/core/rendering/scenegraph/SceneGraph.h
        include/core/rendering/scenegraph/SceneGraphBuildingRule.h
        include/core/rendering/scenegraph/SceneGraphBuilder.h

        include/core/world/World.h
        include/core/world/WorldLayer.h
        include/core/world/WorldLayerLayout.h

        include/utility/OSDefines.h
        include/sdl/utitlity/Path.h
        include/utility/Sleep.h
        include/sdl/utitlity/SDLImageLoader.h

        include/utility/log/LogIncludes.h

        include/test/EntityTest.h
        include/test/SDLTestApplication.h
        include/test/SDLTestApplication2.h

        include/test/trials/enum.h
        include/test/trials/GenericTest.h
        include/test/trials/GenericTypesInMapTest.h
        include/test/trials/TrafoUnionTest.h
        include/core/rendering/scenegraph/sort/RenderableSort.h
        include/core/rendering/scenegraph/sort/RenderableSortComparator.h
        include/test/trials/PrivateHackTest.h
        include/core/event/EventManager.h
        include/core/world/event/EntitySpawnedEvent.h
        include/core/event/Event.h
        include/core/entity/event/EntityEvent.h
        include/core/world/event/EntityDespawnedEvent.h
        include/core/event/EventService.h
        include/test/EventServiceTest.h
        include/core/event/EventListener.h
        include/core/entity/EntityComponentProvider.h
        include/core/entity/event/EntityComponentAddedEvent.h
        include/core/entity/event/EntityComponentEvent.h
        include/core/entity/event/EntityComponentRemovedEvent.h
        include/sdl/SDLScreen.h
        include/sdl/SDLInputSystem.h )

### API INCLUDES ########################################
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

### SUBDIRECTORIES ######################################
add_subdirectory(src)

### EXECUTABLES #########################################
add_executable(PaxEngine3 ${SOURCE_FILES})

### LINKING #############################################
target_link_libraries(PaxEngine3 paxsdl paxtest paxcore)