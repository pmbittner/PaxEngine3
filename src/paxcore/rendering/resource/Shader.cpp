//
// Created by Paul on 08.10.2017.
//

#include <paxcore/rendering/data/Shader.h>

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
        return
                VertexFlags.compare(other.VertexFlags)
                | GeometryFlags.compare(other.GeometryFlags)
                | FragmentFlags.compare(other.FragmentFlags)
                | TessControlFlags.compare(other.TessControlFlags)
                | TessEvaluationFlags.compare(other.TessEvaluationFlags)
                | ComputeFlags.compare(other.ComputeFlags) == 0;
    }



    Shader::Shader(Flags flags) : _flags(flags) {

    }

    void Shader::cacheUniforms(const std::vector<std::string> &uniformNames) {
        for (const std::string& uniformName: uniformNames)
            cacheUniform(uniformName);
    }

    bool Shader::setUniform(const std::string &uniformName, const bool &value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, const float& value) {
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

    bool Shader::setUniform(const std::string &uniformName, const int &value) {
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