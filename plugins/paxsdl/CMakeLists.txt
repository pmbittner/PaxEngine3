### LIBRARIES ########################################
option(WITH_SDL_IMAGE "True if build with SDL2Image" ON)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    set(SDL2_LIBRARY ${PAX_LIB_DIR}/win/lib/SDL2/lib/${PAX_OS_ARCHITECTURE}/SDL2.lib)

    if(WITH_SDL_IMAGE)
        set(SDL2_IMAGE_LIBRARY ${PAX_LIB_DIR}/win/lib/SDL2_image/lib/${PAX_OS_ARCHITECTURE}/SDL2_image.lib)
    endif()
else()
    find_package(SDL2 REQUIRED)

    if(WITH_SDL_IMAGE)
        find_package(SDL2_image REQUIRED)
    endif()

    #find_package(SDL2_ttf REQUIRED)
    #include_directories(${SDL2_TTF_INCLUDE_DIR})

    include_directories(${SDL2_INCLUDE_DIR})
    if(WITH_SDL_IMAGE)
        include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    endif()
endif()

### TARGET ###########################################
set(PAX_SDL_SOURCE_FILES
        src/SDLInputSystem.cpp
        src/SDLKeyboard.cpp
        src/SDLWindow.cpp
        src/SDLPureContext.cpp

        src/opengl/SDLOpenGLWindow.cpp
        src/opengl/SDLOpenGLContext.cpp
        src/SDLImageTextureLoader.cpp
        src/opengl/SDLOpenGLPlugin.cpp)

include_directories(../paxopengl/include/)
include_directories(include)

set(HEADERS_FOR_CLION
        include/paxsdl/opengl/SDLOpenGLPlugin.h
        include/paxsdl/opengl/SDLOpenGLWindow.h
        include/paxsdl/SDLImageTextureLoader.h
        include/paxsdl/SDLInputSystem.h
        include/paxsdl/SDLWindow.h
        include/paxsdl/SDLPureContext.h
        include/paxsdl/SDLKeyboard.h
        include/paxsdl/SDLInputSystem.h

        include/paxsdl/utility/SDLImageLoader.h
        )

add_library(paxsdl
        ${HEADERS_FOR_CLION}
        ${PAX_SDL_SOURCE_FILES}
        )

target_link_libraries(paxsdl ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})

if(WITH_SDL_IMAGE)
    message("Building with SDL_Image")
    target_compile_definitions(paxsdl PUBLIC -DPAX_WITH_SDLIMAGE)
else()
    message("Building without SDL_Image")
endif(WITH_SDL_IMAGE)