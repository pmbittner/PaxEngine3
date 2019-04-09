//
// Created by Paul on 08.10.2017.
//

#include <paxopengl/io/OpenGLShaderLoader.h>

#include "paxopengl/io/OpenGLShaderLoader.h"
#include "paxopengl/resource/OpenGLShader.h"

#include "paxutil/resources/Resources.h"

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

std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                                       const PAX::VariableHierarchy &parameters) {
    Shader::FileInfo fileInfo;
    Shader::Flags flags;

    // required vars
    {
        fileInfo.VertexPath   = parameters.tryGet("Vertex");
        fileInfo.FragmentPath = parameters.tryGet("Fragment");
    }

    // optional vars
#define PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(var, str, vars, op) { \
const auto & it = vars.find(str); \
if (it != vars.end()) { \
    var op it->second; \
}}
    {
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.ComputePath, "Compute", parameters.values, +)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.GeometryPath, "Geometry", parameters.values, +)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.TessControlPath, "TessControl", parameters.values, +)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.TessEvaluationPath, "TessEvaluation", parameters.values, +)
    }

    {
        const auto & flagsIt = parameters.children.find("Flags");
        if (flagsIt != parameters.children.end()) {
            VariableHierarchy flagVars = flagsIt->second;
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.VertexFlags, "Vertex", flagVars.values, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.FragmentFlags, "Fragment", flagVars.values, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.ComputeFlags, "Compute", flagVars.values, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.GeometryFlags, "Geometry", flagVars.values, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.TessControlFlags, "TessControl", flagVars.values, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.TessEvaluationFlags, "TessEvaluation", flagVars.values, +=)
        }
    }

#undef PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS

    return resources.loadOrGet<Shader>(fileInfo, flags);
}
