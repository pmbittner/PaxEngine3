### LIBRARIES ########################################
if (UNIX)
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    #set(GLEW_INCLUDE_DIRS ${PAX_LIB_DIR}/win/lib/glew-2.1.0/include)
    set(GLEW_LIBRARY ${PAX_LIB_DIR}/win/lib/glew-2.1.0/lib/Release/${PAX_OS_ARCHITECTURE}/glew32.lib)
else()
    find_package(GLEW REQUIRED)
endif()

include_directories(${GLEW_INCLUDE_DIRS})

set(PAX_OPENGL_HEADERS_FOR_CLION
        include/paxopengl/OpenGLPlugin.h
        include/paxopengl/factory/OpenGLMeshFactory.h
        include/paxopengl/io/OpenGLShaderLoader.h
        include/paxopengl/io/FreeImageOpenGLTextureLoader.h
        include/paxopengl/OpenGLMacros.h
        include/paxopengl/rendernodes/OpenGLWorldLayerRenderPass.h
        include/paxopengl/resource/OpenGLTexture2D.h
        include/paxopengl/resource/OpenGLMesh.h
        include/paxopengl/resource/OpenGLShader.h
        include/paxopengl/rendernodes/OpenGLContext.h
        include/paxopengl/OpenGLViewport.h
        include/paxopengl/factory/OpenGLViewportFactory.h
        include/paxopengl/OpenGLError.h
        include/paxopengl/rendernodes/OpenGLRenderPass.h
        include/paxopengl/rendernodes/OpenGLRenderPassChannel.h)

set(PAX_OPENGL_SOURCE_FILES
        src/OpenGLViewport.cpp
        src/io/FreeImageOpenGLTextureLoader.cpp
        src/rendernodes/OpenGLWorldLayerRenderPass.cpp
        src/rendernodes/OpenGLContext.cpp
        src/resource/OpenGLTexture2D.cpp
        src/resource/OpenGLMesh.cpp
        src/resource/OpenGLShader.cpp
        src/io/OpenGLShaderLoader.cpp
        src/OpenGLPlugin.cpp
        src/OpenGLError.cpp
        src/rendernodes/OpenGLRenderPassChannel.cpp
        src/rendernodes/OpenGLRenderPass.cpp
        include/paxopengl/factory/OpenGLTextureFactory.h
        src/factory/OpenGLTextureFactory.cpp)

### TARGET ###########################################
include_directories(include)

add_library(paxopengl
        ${PAX_OPENGL_HEADERS_FOR_CLION}
        ${PAX_OPENGL_SOURCE_FILES}
        )

target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})