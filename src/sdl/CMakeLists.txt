add_library(paxsdl SDLInputSystem.cpp SDLWindow.cpp SDLEngineSetup.cpp test/SDLSprite.cpp SDLRenderPass.cpp
        utility/Path.cpp opengl/SDLOpenGLWindow.cpp opengl/SDLOpenGLRenderPass.cpp opengl/SDLOpenGLEngineSetup.cpp SDLRenderFactory.cpp SDLKeyboard.cpp)
target_link_libraries(paxsdl ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})