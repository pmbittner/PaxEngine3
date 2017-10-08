//
// Created by Paul on 08.10.2017.
//

#include <core/rendering/resource/Shader.h>

namespace PAX {
    void Shader::cacheUniforms(const std::vector<std::string> &uniformNames) {
        for (const std::string& uniformName: uniformNames)
            cacheUniform(uniformName);
    }

    bool Shader::setUniform(const std::string &uniformName, float value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, glm::vec2 value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, glm::vec3 value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, glm::vec4 value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, glm::mat3 value) {
        return false;
    }

    bool Shader::setUniform(const std::string &uniformName, glm::mat4 value) {
        return false;
    }
}