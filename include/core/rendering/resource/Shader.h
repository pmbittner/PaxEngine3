//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SHADER_H
#define PAXENGINE3_SHADER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace PAX {
    class Shader {
    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        void cacheUniforms(const std::vector<std::string>& uniformNames);
        virtual void cacheUniform(const std::string& uniformName) = 0;
        virtual bool hasUniform(const std::string& uniformName) = 0;

        virtual bool setUniform(const std::string& uniformName, const float& value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec2& value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec3& value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec4& value);

        virtual bool setUniform(const std::string& uniformName, const int& value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec2& value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec3& value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec4& value);

        virtual bool setUniform(const std::string& uniformName, const glm::mat2& value, bool transpose = false);
        virtual bool setUniform(const std::string& uniformName, const glm::mat3& value, bool transpose = false);
        virtual bool setUniform(const std::string& uniformName, const glm::mat4& value, bool transpose = false);
    };
}

#endif //PAXENGINE3_SHADER_H
