cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### OPTIONS #############################################
option(WITH_SDL_IMAGE "True if build with SDL2Image" ON)
option(WITH_BOX2D "True if 2D physics with Box2D should be integrated" ON)
option(WITH_FBX "True if fbxsdk should be used to support loading FBX files" OFF)

if(WITH_SDL_IMAGE)
    message("Building with: SDL_Image")
    add_definitions(-DPAX_WITH_SDLIMAGE)
endif()

if (WITH_FBX)
    message("Building with: libfbx")
    add_definitions(-DPAX_WITH_FBX)
endif()

if (WITH_BOX2D)
    message("Building with: Box2D")
    add_definitions(-DPAX_WITH_BOX2D)
endif()

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
set(PLATFORM_FLAGS_DEBUG)
set(PLATFORM_FLAGS_RELEASE)

set(LIB_DIR_RELATIVE ../lib)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/${LIB_DIR_RELATIVE})

if (WIN32)
    message("Set flags for WIN32")
    if (${COMPILER_IS_MSVC})
        message("    and MSVC")

        set(PLATFORM_FLAGS         "${PLATFORM_FLAGS} /std:c++latest")
        set(PLATFORM_FLAGS_DEBUG   "${PLATFORM_FLAGS_DEBUG} /MTd")
        set(PLATFORM_FLAGS_RELEASE "${PLATFORM_FLAGS_RELEASE} /MT")
    else(${COMPILER_IS_MSVC}) # condition for nested if
        message("    but not MSVC")
        set(PLATFORM_FLAGS "${PLATFORM_FLAGS} -static -std=c++11")# "-static-libgcc -static-libstdc++") #this may be wrong for unix
    endif(${COMPILER_IS_MSVC}) # condition for nested if
elseif(UNIX)
    message("Set flags for UNIX")
    set(PLATFORM_FLAGS "${PLATFORM_FLAGS} -std=c++11")
    set(PLATFORM_FLAGS_DEBUG "${PLATFORM_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
else(WIN32) # condition for nested if
    message(WARNING "Platform not specified. Correct behaviour not guaranteed.")
endif(WIN32) # condition for nested if


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${PLATFORM_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${PLATFORM_FLAGS_RELEASE}")

message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG  : ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

### PATHS ###############################################
#set(MAIN_FILE Default_main.cpp)

#if (ANDROID)
#        set(MAIN_FILE Android_main.cpp)
#endif()


### SOURCE FILES ########################################

include_directories(include)
include_directories(plugins)

#set(SOURCE_FILES ${MAIN_FILE} src/EngineMain.cpp)

#set(SOURCE_FILES ${SOURCE_FILES}
set(HEADERS_FOR_CLION
        # Header files for CLion

        include/demo/behaviours/RotateAround3D.h
        include/demo/behaviours/Dance2D.h
        include/demo/OpenGL/Cube.h
        include/demo/OpenGL/TerrainDemo.h
        include/demo/Platformer/PlatformerDemo.h
        include/demo/Platformer/PlayerControls.h
        include/demo/Platformer/PlayerSpriteAnimation.h
        include/demo/Platformer/VelocityBehaviour.h
        include/demo/Platformer/FollowEntityBehaviour.h)

### API INCLUDES ########################################

include_directories(${LIB_DIR_RELATIVE}/Easylogging/include)

if (WIN32 AND ${COMPILER_IS_MSVC})
    include_directories(${LIB_DIR_RELATIVE}/win/include)

    set(EASYLOGGING_LIBRARY ${LIB_DIR}/Easylogging/bin/msvc/easylogging.lib)

    if (WITH_FBX)
        set(FBX_LIBRARY debug ${LIB_DIR}/win/lib/libfbxsdk-mtd.lib optimized ${lib_dir}/lib/libfbxsdk-mt.lib)
    endif()

    if (WITH_BOX2D)
        include_directories(${LIB_DIR}/Box2D)
        set(BOX2D_LIBRARY ${LIB_DIR}/Box2D/bin/msvc/box2d.lib)
    endif()

else()
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    link_directories(${LIB_DIR}/Easylogging/bin/mingw)
    set(EASYLOGGING_LIBRARY easylogging)

    if (WITH_FBX)
       message(WARNING "FBX loading is not supported yet!" )
    endif()

    if (WITH_BOX2D)
        include_directories(${LIB_DIR}/Box2D)
        link_directories(${LIB_DIR}/Box2D/bin/mingw)
        set(BOX2D_LIBRARY box2d)
    endif()
endif()

### SUBDIRECTORIES ######################################
add_subdirectory(src)


### PLUGINS #############################################
add_subdirectory(plugins)


### EXECUTABLES #########################################
#add_executable(PaxEngine3 ${SOURCE_FILES})
#target_link_libraries(PaxEngine3 ${EASYLOGGING_LIBRARY} paxphysics paxutil paxsdl paxopengl paxcore)
#set_target_properties( yourexe PROPERTIES RUNTIME_OUTPUT_DIRECTORY E:/parsec/bin/ )

#add_executable(ResourceTest src/test/ResourceTest.cpp include/utility/stdutils/TuplePrinter.h include/utility/stdutils/Templates.h)
#target_link_libraries(ResourceTest paxio paxutil paxlib)
