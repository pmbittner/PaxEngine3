//
// Created by Paul on 08.10.2017.
//

#include <core/rendering/resource/Shader.h>

namespace PAX {
    void Shader::cacheUniforms(const std::vector<std::string> &uniformNames) {
        for (const std::string& uniformName: uniformNames)
            cacheUniform(uniformName);
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