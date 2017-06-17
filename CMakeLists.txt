cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### FLAGS ###############################################
set(PLATFORM_FLAGS)

if (WIN32)
        set(PLATFORM_FLAGS "-static")# "-static-libgcc -static-libstdc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${PLATFORM_FLAGS}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(MAIN_FILE Default_main.cpp)

if (ANDROID)
        set(MAIN_FILE Android_main.cpp)
else()

endif()

### SOURCE FILES ########################################
set(SOURCE_FILES ${MAIN_FILE} src/EngineMain.cpp src/lib/easylogging++.cc
        # Header files for CLion
        include/lib/easylogging++.h

        include/core/Engine.h
        include/core/Game.h
        include/core/io/InputSystem.h

        include/core/entity/Entity.h
        include/core/entity/EntityComponent.h
        include/core/entity/EntityComponentPool.h
        include/core/entity/Transform.h

        include/core/system/EngineSystem.h
        include/core/system/EntityComponentSystem.h

        include/core/io/Keyboard.h
        include/core/io/Mouse.h

        include/core/rendering/Renderable.h
        include/core/rendering/Renderer.h
        include/core/rendering/Graphics.h

        include/core/rendering/scenegraph/SceneGraph.h
        include/core/rendering/scenegraph/SceneGraphBuildingRule.h
        include/core/rendering/scenegraph/SceneGraphGenerator.h
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
        include/utility/stdutils.h
        include/test/SceneGraphTest.h
        include/core/rendering/scenegraph/EntitySceneGraph.h
        include/test/trials/DelegateTest.h
        include/core/event/Delegate.h
        include/core/event/EventHandler.h
        include/core/entity/event/EntityParentChangedEvent.h
        include/test/trials/StaticMember.h
        include/demo/SDLDemo.h
        include/sdl/test/SDLSprite.h
        include/sdl/SDLRenderPass.h
        include/test/trials/SpecializedFunctionWithDifferentReturType.h
        include/utility/MacroIncludes.h
        include/core/rendering/scenegraph/ListSceneGraphGenerator.h
        include/core/system/BehaviourSystem.h
        include/core/entity/component/Behaviour.h
        include/demo/MoveToMouseBehaviour.h
        include/core/io/MouseButtonPressedEvent.h
        include/core/io/MouseButtonReleasedEvent.h
        include/core/io/MouseButtonEvent.h
        include/core/time/Time.h
        include/sdl/opengl/SDLOpenGLWindow.h
        include/opengl/OpenGLRenderPass.h
        include/demo/OpenGLDemo.h
        include/sdl/opengl/SDLOpenGLSetup.h)

### API INCLUDES ########################################
if (ANDROID)
        set(ANDROID_LIBS_INCLUDE_DIR lib/Android/include)

        include_directories(${ANDROID_LIBS_INCLUDE_DIR})

        #find_package(SDL2 REQUIRED)
        include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)
        include(${PROJECT_SOURCE_DIR}/cmake/android.cmake)
        set ( SDL2_LIBRARY SDL2 )
        #link_directories(${PROJECT_SOURCE_DIR}/lib/Android/SDL/armeabi-v7a)
        #FIND_LIBRARY(SDL2_LIBRARY NAMES libSDL2.so PATHS lib/Android/SDL/armeabi-v7a)
        #find_library(SDL2_LIBRARY NAMES SDL SDL2 libSDL2.so libSDL2 HINTS "${PROJECT_SOURCE_DIR}/lib/Android/SDL/armeabi-v7a")
        #set(SDL2_LIBRARY SDL2)
else()
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIR})

        #find_package(SDL2_ttf REQUIRED)
        #include_directories(${SDL2_TTF_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

### SUBDIRECTORIES ######################################
add_subdirectory(src)

### EXECUTABLES #########################################
if (ANDROID)
        add_library(PaxEngine3 SHARED ${SOURCE_FILES})
else()
        add_executable(PaxEngine3 ${SOURCE_FILES})
endif()

### LINKING #############################################
target_link_libraries(PaxEngine3 paxsdl paxopengl paxtest paxcore)