add_library(paxopengl OpenGLRenderPass.cpp)
target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})# ${SDL2_TTF_LIBRARIES})