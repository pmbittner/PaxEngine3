find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(PAX_OPENGL_SOURCE_FILES
        src/OpenGLViewport.cpp
        src/io/FreeImageOpenGLTextureLoader.cpp
        src/rendernodes/OpenGLDefaultWorldSceneGraph.cpp
        src/rendernodes/OpenGLContext.cpp
        src/resource/OpenGLTexture2D.cpp
        src/resource/OpenGLMesh.cpp
        src/resource/OpenGLShader.cpp
        src/io/OpenGLShaderLoader.cpp
        src/OpenGLPlugin.cpp
        src/OpenGLError.cpp
        src/rendernodes/OpenGLRenderPass.cpp
        src/factory/OpenGLTextureFactory.cpp
        src/OpenGLPointCloudSettings.cpp
        src/factory/OpenGLRenderPassFactory.cpp
        src/Conversion.cpp
        src/glslpreprocessor/GLSLPreprocessorService.cpp
        src/glslpreprocessor/GLSLIncludeDirectives.cpp)

add_library(paxopengl ${PAX_OPENGL_SOURCE_FILES})
add_library(PaxEngine3::opengl ALIAS paxopengl)
target_include_directories(paxopengl PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxopengl PUBLIC paxcore OpenGL::GL GLEW::GLEW)
