//
// Created by Paul on 08.10.2017.
//

#include <resource/OpenGLShaderLoader.h>
#include <resource/OpenGLShader.h>

bool PAX::OpenGL::OpenGLShaderLoader::canLoad(Shader::FileInfo fileInfo) const {
    return true;
}

bool PAX::OpenGL::OpenGLShaderLoader::canLoad(Shader::FileInfo fileInfo, Shader::Flags flags) const {
    return true;
}

std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::load(Shader::FileInfo fileInfo) {
    auto shader = std::make_shared<OpenGLShader>(fileInfo.VertexPath, fileInfo);
    shader->initialize();
    return shader;
}

std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::load(Shader::FileInfo fileInfo, Shader::Flags flags) {
    auto shader = std::make_shared<OpenGLShader>(fileInfo.VertexPath, fileInfo, flags);
    shader->initialize();
    return shader;
}