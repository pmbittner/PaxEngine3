//
// Created by Paul on 08.10.2017.
//

#include <paxcore/rendering/data/Shader.h>
#include <paxcore/OStreamOverloads.h>

namespace PAX {
    Shader::Flags::Flags() {
        reset();
    }

    void Shader::Flags::reset() {
        VertexFlags = "";
        GeometryFlags = "";
        FragmentFlags = "";
        TessControlFlags = "";
        TessEvaluationFlags = "";
        ComputeFlags = "";
    }

    bool Shader::Flags::operator==(const Flags &other) const {
        return   (VertexFlags.compare(other.VertexFlags)
                | GeometryFlags.compare(other.GeometryFlags)
                | FragmentFlags.compare(other.FragmentFlags)
                | TessControlFlags.compare(other.TessControlFlags)
                | TessEvaluationFlags.compare(other.TessEvaluationFlags)
                | ComputeFlags.compare(other.ComputeFlags)) == 0;
    }

    Shader::FileInfo::FileInfo() = default;

    Shader::FileInfo::FileInfo(const PAX::Path &vertexPath, const PAX::Path &fragmentPath) : VertexPath(vertexPath), FragmentPath(fragmentPath) {}

    bool Shader::FileInfo::operator==(const PAX::Shader::FileInfo &other) const {
        return VertexPath == other.VertexPath
            && GeometryPath == other.GeometryPath
            && FragmentPath == other.FragmentPath
            && TessControlPath == other.TessControlPath
            && TessEvaluationPath == other.TessEvaluationPath
            && ComputePath == other.ComputePath;
    }


    Shader::Shader(const FileInfo & fileInfo, const Flags & flags) : _fileInfo(fileInfo), _flags(flags) {

    }

    Shader::~Shader() = default;

    void Shader::initialize() {
        upload();
        detectUniforms();
    }

    const Shader::FileInfo & Shader::getFileInfo() const {
        return _fileInfo;
    }

    bool Shader::setUniform(const std::string &uniformName, bool value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, float value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::vec2& value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::vec3& value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::vec4& value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, int value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::ivec2 &value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::ivec3 &value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::ivec4 &value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::mat2 &value, bool transpose) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::mat3& value, bool transpose) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const glm::mat4& value, bool transpose) {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, PAX::Shader::Flags const &flags) {
    return os << "Flags[\n\tVertex: " << flags.VertexFlags
              << "\n\tGeometry " << flags.GeometryFlags
              << "\n\tFragment " << flags.FragmentFlags
              << "\n\tTessControl " << flags.TessControlFlags
              << "\n\tTessEvaluation " << flags.TessEvaluationFlags
              << "\n\tCompute " << flags.ComputeFlags + "\n]";
}

std::ostream &operator<<(std::ostream &os, PAX::Shader::FileInfo const &fileInfo) {
    return os << "Flags[\n\tVertex: " << fileInfo.VertexPath
              << "\n\tGeometry " << fileInfo.GeometryPath
              << "\n\tFragment " << fileInfo.FragmentPath
              << "\n\tTessControl " << fileInfo.TessControlPath
              << "\n\tTessEvaluation " << fileInfo.TessEvaluationPath
              << "\n\tCompute " << fileInfo.ComputePath + "\n]";
}