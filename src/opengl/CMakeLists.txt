#find_package(FreeImage REQUIRED)
#if (FreeImage_FOUND)
#    include_directories(${FreeImage_INCLUDE_DIRS})
#
#    message("FreeImage found")
#    message("    ${FreeImage_INCLUDE_DIRS}")
#    message("    ${FreeImage_LIBRARIES}")
#
#    #add_definitions(-DPAX_WITH_FREEIMAGE)
#else()
#    message("FreeImage not found!")
#endif()

add_library(paxopengl rendernodes/OpenGLRenderPass.cpp OpenGLViewport.cpp resource/OpenGLTexture2D.cpp resource/OpenGLMesh.cpp resource/OpenGLShader.cpp rendernodes/OpenGLWorldLayerRenderPass.cpp OpenGLRenderFactory.cpp OpenGLSprite.cpp resource/OpenGLShaderLoader.cpp io/FreeImageOpenGLTextureLoader.cpp resource/NullOpenGLTextureLoader.cpp rendernodes/OpenGLMeshNode.cpp rendernodes/OpenGLTexturingNode.cpp)
target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY}) #${FreeImage_LIBRARIES} #${SDL2_TTF_LIBRARIES})