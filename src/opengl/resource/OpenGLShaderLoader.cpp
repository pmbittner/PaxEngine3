//
// Created by Paul on 08.10.2017.
//

#include <opengl/resource/OpenGLShaderLoader.h>
#include <opengl/resource/OpenGLShader.h>

bool PAX::OpenGL::OpenGLShaderLoader::canLoad(Path vertexShaderPath, Path fragmentShaderPath) {
    return true;
}

PAX::Shader *PAX::OpenGL::OpenGLShaderLoader::load(Path vertexShaderPath, Path fragmentShaderPath) {
    OpenGLShader* shader = new OpenGLShader(vertexShaderPath, vertexShaderPath, fragmentShaderPath);
    return shader;
}

bool PAX::OpenGL::OpenGLShaderLoader::free(Shader *res) {
    delete res;
    return true;
}
