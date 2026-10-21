option(WITH_SDL_IMAGE "True if build with SDL2Image" ON)

find_package(SDL2 REQUIRED)
if(WITH_SDL_IMAGE)
    find_package(SDL2_image REQUIRED)
endif()

set(PAX_SDL_SOURCE_FILES
        src/SDLInputSystem.cpp
        src/SDLKeyboard.cpp
        src/SDLWindow.cpp
        src/SDLPureContext.cpp

        src/opengl/SDLOpenGLWindow.cpp
        src/opengl/SDLOpenGLContext.cpp
        src/SDLTextureLoader.cpp
        src/opengl/SDLOpenGLPlugin.cpp
        src/SDLImageLoader.cpp)

add_library(paxsdl ${PAX_SDL_SOURCE_FILES})
add_library(PaxEngine3::sdl ALIAS paxsdl)
target_include_directories(paxsdl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
# paxsdl includes the SDL-OpenGL link plugin, which needs the OpenGL plugin.
target_link_libraries(paxsdl PUBLIC paxcore paxopengl SDL2::SDL2)
if(WITH_SDL_IMAGE)
    target_link_libraries(paxsdl PUBLIC SDL2_image::SDL2_image)
    target_compile_definitions(paxsdl PUBLIC PAX_WITH_SDLIMAGE)
endif()
