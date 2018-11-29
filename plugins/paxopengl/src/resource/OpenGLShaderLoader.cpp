//
// Created by Paul on 08.10.2017.
//

#include <resource/OpenGLShaderLoader.h>
#include <resource/OpenGLShader.h>

bool PAX::OpenGL::OpenGLShaderLoader::canLoad(Path vertexShaderPath, Path fragmentShaderPath) {
    return true;
}

bool PAX::OpenGL::OpenGLShaderLoader::canLoad(Shader::Flags flags, Path vertexShaderPath, Path fragmentShaderPath) {
    return true;
}

std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::load(Path vertexShaderPath, Path fragmentShaderPath) {
    auto shader = std::make_shared<OpenGLShader>(vertexShaderPath, vertexShaderPath, fragmentShaderPath);
    shader->initialize();
    return shader;
}

std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::load(Shader::Flags flags, Path vertexShaderPath, Path fragmentShaderPath) {
    auto shader = std::make_shared<OpenGLShader>(vertexShaderPath, vertexShaderPath, fragmentShaderPath, flags);
    shader->initialize();
    return shader;
}