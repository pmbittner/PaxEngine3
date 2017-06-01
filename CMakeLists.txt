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

        include/core/EngineSystem.h
        include/core/GameSystem.h

        include/core/io/Keyboard.h
        include/core/io/Mouse.h

        include/core/rendering/Renderable.h
        include/core/rendering/Renderer.h
        include/core/rendering/Graphics.h

        include/core/rendering/scenegraph/SceneGraph.h
        include/core/rendering/scenegraph/SceneGraphBuildingRule.h
        include/core/rendering/scenegraph/SceneGraphBuilder.h
        include/core/rendering/scenegraph/sort/RenderableSort.h
        include/core/rendering/scenegraph/sort/RenderableSortComparator.h

        include/core/world/World.h
        include/core/world/WorldLayer.h
        include/core/world/WorldLayerLayout.h

        include/utility/OSDefines.h
        include/utility/Sleep.h

        include/utility/log/LogIncludes.h

        include/test/EntityTest.h
        include/test/SDLTestApplication.h
        include/test/SDLTestApplication2.h
        include/test/trials/enum.h
        include/test/trials/GenericTest.h
        include/test/trials/GenericTypesInMapTest.h
        include/test/trials/TrafoUnionTest.h
        include/test/trials/PrivateHackTest.h

        include/sdl/utitlity/Path.h
        include/sdl/utitlity/SDLImageLoader.h

        include/core/event/Event.h
        include/core/event/EventService.h
        include/core/entity/event/EntityEvent.h
        include/core/world/event/EntitySpawnedEvent.h
        include/core/world/event/EntityDespawnedEvent.h
        include/test/EventServiceTest.h
        include/core/event/EventListener.h
        include/core/entity/EntityComponentProvider.h
        include/core/entity/event/EntityComponentAddedEvent.h
        include/core/entity/event/EntityComponentEvent.h
        include/core/entity/event/EntityComponentRemovedEvent.h
        include/sdl/SDLInputSystem.h
        include/core/io/Window.h
        include/sdl/SDLWindow.h
        include/core/EngineSetup.h
        include/sdl/SDLEngineSetup.h
        include/core/rendering/Camera.h
        include/sdl/SDLInputSystem.h
        include/core/rendering/scenegraph/rule/GroupByEntitySceneGraphBuildingRule.h
        include/core/rendering/scenegraph/rule/ListSceneGraphBuildingRule.h
        include/test/trials/FriendTest.h
        include/test/trials/InheritanceTest.h
        include/utility/stdutils.h include/test/SceneGraphTest.h include/core/rendering/scenegraph/EntitySceneGraph.h include/test/trials/DelegateTest.h include/core/event/Delegate.h include/core/event/EventHandler.h include/core/entity/event/EntityParentChangedEvent.h include/test/trials/StaticMember.h include/demo/DemoGame.h include/sdl/test/SDLSprite.h)

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