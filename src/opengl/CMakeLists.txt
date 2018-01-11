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

add_library(paxopengl
        OpenGLViewport.cpp
        OpenGLRenderFactory.cpp
        io/FreeImageOpenGLTextureLoader.cpp
        rendernodes/OpenGLWorldLayerRenderPass.cpp
        rendernodes/OpenGLRenderPass.cpp
        resource/OpenGLTexture2D.cpp
        resource/OpenGLMesh.cpp
        resource/OpenGLShader.cpp
        resource/OpenGLShaderLoader.cpp
        resource/NullOpenGLTextureLoader.cpp
        resource/OpenGLSpriteSheet.cpp utility/Error.cpp)
target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY}) #${FreeImage_LIBRARIES} #${SDL2_TTF_LIBRARIES})