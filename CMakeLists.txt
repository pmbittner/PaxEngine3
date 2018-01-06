cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### DETECT COMPILER #####################################
set(COMPILER_IS_CLANG FALSE)
set(COMPILER_IS_GCC FALSE)
set(COMPILER_IS_INTEL FALSE)
set(COMPILER_IS_MSVC FALSE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    set(COMPILER_IS_CLANG TRUE)
    message("Compiler set to CLANG")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(COMPILER_IS_GCC TRUE)
    message("Compiler set to GCC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
    set(COMPILER_IS_INTEL TRUE)
    message("Compiler set to INTEL")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
    set(COMPILER_IS_MSVC TRUE)
    message("Compiler set to MSVC")
endif()

### FLAGS ###############################################
set(PLATFORM_FLAGS)

set(LIB_DIR_RELATIVE ../lib)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/${LIB_DIR_RELATIVE})

if (WIN32 AND ${COMPILER_IS_MSVC})
    set(LIB_DIR_RELATIVE ../lib/win)
    set(LIB_DIR ${CMAKE_SOURCE_DIR}/${LIB_DIR_RELATIVE})

    set(PLATFORM_FLAGS ${PLATFORM_FLAGS} "/std:c++latest")

else()
    set(PLATFORM_FLAGS ${PLATFORM_FLAGS} "-static")# "-static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_FLAGS}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


### OPTIONS #############################################
option(WITH_SDL_IMAGE "True if build with SDL2Image" ON)
option(WITH_FBX "True if fbxsdk should be used to support loading FBX files" ON)


### PATHS ###############################################
set(MAIN_FILE Default_main.cpp)

if (ANDROID)
        set(MAIN_FILE Android_main.cpp)
endif()


### SOURCE FILES ########################################

include_directories(include)

set(SOURCE_FILES
        # actual source files for PaxEngine3
        ${MAIN_FILE}
        src/EngineMain.cpp

        # Header files for CLion
        include/lib/easylogging++.h

        include/core/Engine.h
        include/core/Game.h
        include/core/io/InputSystem.h

        include/core/entity/Entity.h
        include/core/entity/EntityComponent.h
        include/core/entity/component/allocators/EntityComponentPool.h
        include/core/entity/Transform.h

        include/core/system/EngineSystem.h
        include/core/system/EntityComponentSystem.h

        include/core/io/Keyboard.h
        include/core/io/Mouse.h

        include/core/rendering/interface/Renderable.h
        include/core/rendering/Renderer.h
        include/core/rendering/Graphics.h

        include/core/rendering/resource/Shader.h

        include/core/rendering/scenegraph/SceneGraphGenerator.h
        include/core/rendering/scenegraph/sort/GraphicsSort.h
        include/core/rendering/scenegraph/sort/GraphicsSortComparator.h

        include/core/world/World.h
        include/core/world/WorldLayer.h
        include/core/world/WorldLayerLayout.h

        include/utility/macros/OSDefines.h
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

        include/sdl/utility/Path.h
        include/sdl/utility/SDLImageLoader.h

        include/demo/behaviours/MoveToMouseBehaviour.h
        include/demo/behaviours/RotateAround3D.h
        include/demo/behaviours/Dance2D.h
        include/demo/OpenGL/RenderTests.h
        include/demo/OpenGL/Cube.h

        include/core/event/Event.h
        include/core/event/EventService.h
        include/core/entity/event/EntityEvent.h
        include/core/world/event/EntitySpawnedEvent.h
        include/core/world/event/EntityDespawnedEvent.h
        include/test/EventServiceTest.h
        include/core/event/EventListener.h
        include/core/entity/EntityComponentAllocator.h
        include/core/entity/event/EntityComponentAddedEvent.h
        include/core/entity/event/EntityComponentEvent.h
        include/core/entity/event/EntityComponentRemovedEvent.h
        include/sdl/SDLInputSystem.h
        include/core/io/Window.h
        include/sdl/SDLWindow.h
        include/core/EngineSetup.h
        include/sdl/SDLEngineSetup.h
        include/core/rendering/camera/Camera.h
        include/sdl/SDLInputSystem.h
        include/test/trials/FriendTest.h
        include/test/trials/InheritanceTest.h
        include/utility/stdutils/CollectionUtils.h
        include/test/SceneGraphTest.h
        include/test/trials/DelegateTest.h
        include/core/event/Delegate.h
        include/core/event/EventHandler.h
        include/core/entity/event/EntityParentChangedEvent.h
        include/test/trials/StaticMember.h
        include/sdl/SDLRenderPass.h
        include/sdl/SDLKeyboard.h
        include/test/trials/SpecializedFunctionWithDifferentReturType.h
        include/utility/macros/MacroIncludes.h
        include/core/system/BehaviourSystem.h
        include/core/entity/component/Behaviour.h

        include/core/io/event/MouseButtonPressedEvent.h
        include/core/io/event/MouseButtonReleasedEvent.h
        include/core/io/event/MouseButtonEvent.h
        include/core/time/Time.h
        include/sdl/opengl/SDLOpenGLWindow.h
        include/opengl/rendernodes/OpenGLRenderPass.h
        include/sdl/opengl/SDLOpenGLEngineSetup.h
        include/core/rendering/Viewport.h
        include/opengl/OpenGLViewport.h
        include/core/rendering/scenegraph/nodes/TexturingNode.h
        include/core/rendering/resource/Mesh.h
        include/core/rendering/resource/Texture.h
        include/opengl/resource/OpenGLTexture2D.h
        include/opengl/resource/OpenGLMesh.h
        include/opengl/resource/OpenGLShader.h
        include/core/rendering/camera/Projection.h
        include/core/rendering/camera/PerspectiveProjection.h
        include/core/rendering/RenderOptions.h
        include/opengl/deprecated/test.h
        include/opengl/rendernodes/OpenGLWorldLayerRenderPass.h
        include/core/rendering/RenderFactory.h
        include/sdl/SDLRenderFactory.h
        include/opengl/OpenGLRenderFactory.h
        include/opengl/OpenGLMacros.h
        include/opengl/OpenGLSprite.h
        include/utility/io/CSVSettingsLoader.h
        include/utility/io/CSVRow.h
        include/utility/StringUtils.h
        include/core/rendering/camera/FullPixelScreenProjection.h
        include/core/io/event/ResolutionChangedEvent.h
        include/test/trials/InvisibleMixinTest.h
        include/core/entity/EntityComponentDependency.h
        include/utility/reflection/MemberCheck.h
        include/utility/Dependency.h
        include/core/io/resources/Resources.h
        include/utility/datastructures/TypeMap.h
        include/utility/Signature.h
        include/test/ResourcesTest.h
        include/core/io/resources/ResourceLoader.h
        include/core/io/resources/ResourceHandle.h
        include/core/service/Services.h
        include/core/rendering/scenegraph/nodes/SortingNode.h
        include/core/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h
        include/core/rendering/event/ShaderChangedEvent.h
        include/core/rendering/scenegraph/nodes/ShadingNode.h
        include/core/rendering/event/GraphicsShaderChangedEvent.h
        include/opengl/resource/OpenGLShaderLoader.h
        include/opengl/io/FreeImageOpenGLTextureLoader.h
        include/sdl/opengl/SDLImageOpenGLTextureLoader.h
        include/utility/io/FormatChecker.h
        include/core/rendering/scenegraph/SceneGraph.h
        include/opengl/resource/NullOpenGLTextureLoader.h
        include/utility/math/Conversion.h
        include/generation/terrain/TerrainGenerator.h
        include/generation/terrain/Terrain.h
        include/generation/grid/GridGenerator.h
        include/core/rendering/data/CPUMesh.h
        include/core/entity/component/allocators/EntityComponentMallocAllocator.h
        include/core/entity/EntityComponentService.h
        include/test/trials/AllocatorConstructorTest.h
        include/test/trials/InheritedTemplateTypeTest.h
        include/core/io/event/KeyEvent.h
        include/core/io/event/KeyPressedEvent.h
        include/core/io/event/KeyReleasedEvent.h
        include/core/io/MouseButtons.h
        include/core/io/event/MouseWheelEvent.h
        include/core/io/event/MouseEvent.h
        include/core/service/Paths.h
        include/generation/grid/Grid.h
        include/core/rendering/scenegraph/nodes/MeshNode.h
        include/opengl/rendernodes/OpenGLMeshNode.h
        include/opengl/rendernodes/OpenGLTexturingNode.h
        include/core/rendering/SceneGraphGraphics.h
        include/demo/OpenGL/TerrainDemo.h
        include/demo/OpenGL/OpenGLDemo.h
        include/core/entity/component/behaviours/NoClipControls.h
        include/core/io/event/MouseMovedEvent.h
        include/utility/reflection/TemplateTypeToString.h
        include/utility/macros/CompilerDetection.h include/fbx/FBXLoader.h include/fbx/FBXModel.h include/core/animation/Animation.h include/core/rendering/resource/SpriteSheet.h include/demo/OpenGL/Platformer/JumpNRunDemo.h include/core/rendering/scenegraph/nodes/TransformationNode.h include/demo/OpenGL/Platformer/PlayerControls.h include/core/io/resources/Path.h include/core/rendering/scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.h include/opengl/OpenGLRenderFactory2D.h)

### API INCLUDES ########################################

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})


if(WITH_SDL_IMAGE)
    add_definitions(-DPAX_WITH_SDLIMAGE)
endif()

if (WITH_FBX)
    add_definitions(-DPAX_WITH_FBX)
endif()

if (WIN32 AND ${COMPILER_IS_MSVC})
    include_directories(${LIB_DIR_RELATIVE}/include)

    set(GLEW_LIBRARY ${LIB_DIR}/lib/glew32.lib)
    set(SDL2_LIBRARY ${LIB_DIR}/lib/SDL2-2.0.7/lib/x64/SDL2.lib)

    if(WITH_SDL_IMAGE)
        set(SDL2_IMAGE_LIBRARY ${LIB_DIR}/lib/SDL2_image-2.0.2/lib/x64/SDL2_image.lib)
    endif()

    if (WITH_FBX)
        set(FBX_LIBRARY debug ${lib_dir}/lib/libfbxsdk-mtd.lib optimized ${lib_dir}/lib/libfbxsdk-mt.lib)
    endif()

else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    if(WITH_SDL_IMAGE)
        find_package(SDL2_image REQUIRED)
        include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    endif()

    if (WITH_FBX)
        message(SEND_ERROR "FBX loading is not supported yet!" )
    endif()

    #find_package(SDL2_ttf REQUIRED)
    #include_directories(${SDL2_TTF_INCLUDE_DIR})

    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()


### SUBDIRECTORIES ######################################
add_subdirectory(src)


### EXECUTABLES #########################################
add_executable(PaxEngine3 ${SOURCE_FILES})
target_link_libraries(PaxEngine3 paxfbx paxlib paxgeneration paxutil paxsdl paxopengl paxcore)

add_executable(ResourceTest src/test/ResourceTest.cpp include/utility/stdutils/TuplePrinter.h include/utility/stdutils/Templates.h)
target_link_libraries(ResourceTest paxio paxutil paxlib)
