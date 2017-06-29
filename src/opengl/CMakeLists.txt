add_library(paxopengl OpenGLRenderPass.cpp OpenGLViewport.cpp)
target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})