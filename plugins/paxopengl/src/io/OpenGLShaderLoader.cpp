//
// Created by Paul on 08.10.2017.
//

#include <paxopengl/io/OpenGLShaderLoader.h>

#include "paxopengl/io/OpenGLShaderLoader.h"
#include "paxopengl/resource/OpenGLShader.h"

#include "paxutil/resources/Resources.h"

#include "polypropylene/serialisation/json/nlohmann/Json.h"
#include "polypropylene/serialisation/json/JsonUtil.h"

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

//*
std::shared_ptr<PAX::Shader> PAX::OpenGL::OpenGLShaderLoader::loadOrGetFromJson(Resources & resources, const nlohmann::json & j) const {
    Shader::FileInfo fileInfo;
    Shader::Flags flags;

    // required vars
    {
        fileInfo.VertexPath   = j["Vertex"];
        fileInfo.FragmentPath = j["Fragment"];
    }

    // optional vars
#define PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(var, str, vars, op) { \
const auto & it = vars.find(str); \
if (it != vars.end()) { \
    var op ::PAX::JsonToString(it.value()); \
}}

    {
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.ComputePath, "Compute", j, =)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.GeometryPath, "Geometry", j, =)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.TessControlPath, "TessControl", j, =)
        PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(fileInfo.TessEvaluationPath, "TessEvaluation", j, =)
    }

    {
        const auto & flagsIt = j.find("Flags");
        if (flagsIt != j.end()) {
            const nlohmann::json & flagVars = flagsIt.value();
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.VertexFlags, "Vertex", flagVars, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.FragmentFlags, "Fragment", flagVars, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.ComputeFlags, "Compute", flagVars, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.GeometryFlags, "Geometry", flagVars, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.TessControlFlags, "TessControl", flagVars, +=)
            PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS(flags.TessEvaluationFlags, "TessEvaluation", flagVars, +=)
        }
    }

#undef PAX_OPENGLSHADERLOADER_GETFROMVARREG_IFEXISTS

    return resources.loadOrGet<Shader>(fileInfo, flags);
}
//*/