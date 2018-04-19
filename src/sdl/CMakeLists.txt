add_library(paxsdl
        SDLInputSystem.cpp
        SDLKeyboard.cpp
        SDLWindow.cpp
        SDLEngineSetup.cpp
        SDLRenderPass.cpp

        utility/Path.cpp

        opengl/SDLOpenGLWindow.cpp
        opengl/SDLOpenGLRenderPass.cpp
        opengl/SDLOpenGLEngineSetup.cpp
        opengl/SDLImageOpenGLTextureLoader.cpp

        )

target_link_libraries(paxsdl ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})