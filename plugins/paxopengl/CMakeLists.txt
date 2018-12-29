### LIBRARIES ########################################
if (UNIX)
    set(OpenGL_GL_PREFERENCE "GLVND")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    set(GLEW_LIBRARY ${PAX_LIB_DIR}/win/lib/glew-2.1.0/lib/Release/${PAX_OS_ARCHITECTURE}/glew32.lib)
else()
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()


### TARGET ###########################################
find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)

# TODO: Make it possible to have two plugins in one module. Now information is doubled!!!!!!
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/OpenGLEnginePlugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::OpenGL ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/OpenGLEnginePlugin.generated.cpp OpenGLEnginePlugin
        COMMENT "Precompiling PAX::OpenGL (via Python)"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        VERBATIM
)

include_directories(include)

set(HEADERS_FOR_CLION
        include/OpenGLEnginePlugin.h
        include/factory/OpenGLMeshFactory.h
        include/resource/OpenGLSpriteSheet.h
        include/utility/Error.h
        include/resource/NullOpenGLTextureLoader.h
        include/resource/OpenGLShaderLoader.h
        include/io/FreeImageOpenGLTextureLoader.h
        include/OpenGLMacros.h
        include/rendernodes/OpenGLWorldLayerRenderPass.h
        include/resource/OpenGLTexture2D.h
        include/resource/OpenGLMesh.h
        include/resource/OpenGLShader.h
        include/rendernodes/OpenGLRenderPass.h
        include/OpenGLViewport.h
        include/factory/OpenGLViewportFactory.h)

add_library(paxopengl
        ${HEADERS_FOR_CLION}
        src/OpenGLViewport.cpp
        src/io/FreeImageOpenGLTextureLoader.cpp
        src/rendernodes/OpenGLWorldLayerRenderPass.cpp
        src/rendernodes/OpenGLRenderPass.cpp
        src/resource/OpenGLTexture2D.cpp
        src/resource/OpenGLMesh.cpp
        src/resource/OpenGLShader.cpp
        src/resource/OpenGLShaderLoader.cpp
        src/resource/NullOpenGLTextureLoader.cpp
        src/resource/OpenGLSpriteSheet.cpp
        src/utility/Error.cpp
        src/OpenGLEnginePlugin.cpp
        src/OpenGLEnginePlugin.generated.cpp
        )

target_link_libraries(paxopengl ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})