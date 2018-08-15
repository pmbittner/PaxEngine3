### LIBRARIES ########################################
if (WIN32 AND ${COMPILER_IS_MSVC})
    set(SDL2_LIBRARY ${LIB_DIR}/win/lib/SDL2-2.0.7/lib/x64/SDL2.lib)

    if(WITH_SDL_IMAGE)
        set(SDL2_IMAGE_LIBRARY ${LIB_DIR}/win/lib/SDL2_image-2.0.2/lib/x64/SDL2_image.lib)
    endif()
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    if(WITH_SDL_IMAGE)
        find_package(SDL2_image REQUIRED)
        include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    endif()

    #find_package(SDL2_ttf REQUIRED)
    #include_directories(${SDL2_TTF_INCLUDE_DIR})
endif()


### TARGET ###########################################

find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEnginePlugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::SDL ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEnginePlugin.generated.cpp SDLEnginePlugin
        COMMENT "Precompiling PAX::SDL (via Python)"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        VERBATIM
)

include_directories(../opengl/include/)
include_directories(include)

set(HEADERS_FOR_CLION
        include/opengl/SDLOpenGLEnginePlugin.h
        include/opengl/SDLImageOpenGLTextureLoader.h
        include/opengl/SDLOpenGLWindow.h
        include/SDLInputSystem.h
        include/SDLWindow.h
        include/SDLRenderPass.h
        include/SDLKeyboard.h
        include/SDLImageLoader.h
        include/SDLInputSystem.h

        include/utility/Path.h
        include/utility/SDLImageLoader.h
        )

add_library(paxsdl
        ${HEADERS_FOR_CLION}
        src/SDLInputSystem.cpp
        src/SDLKeyboard.cpp
        src/SDLWindow.cpp
        src/SDLRenderPass.cpp

        src/utility/Path.cpp

        src/opengl/SDLOpenGLWindow.cpp
        src/opengl/SDLOpenGLRenderPass.cpp
        src/opengl/SDLImageOpenGLTextureLoader.cpp

        src/SDLEnginePlugin.generated.cpp
        )

target_link_libraries(paxsdl ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})