//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SHADER_H
#define PAXENGINE3_SHADER_H

#include <string>
#include <vector>
#include <ostream>

#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    class Shader {
    public:
        /**
         * Compiling flags for shader files like macros in C/C++.
         * They have to be complete, meaning that no prefixes (like "#define") or linebreaks will be added automatically.
         *
         */
        struct Flags {
            std::string VertexFlags;
            std::string GeometryFlags;
            std::string FragmentFlags;
            std::string TessControlFlags;
            std::string TessEvaluationFlags;
            std::string ComputeFlags;

            Flags();
            void reset();
            bool operator==(const Flags& other) const;
        };

    protected:
        Flags _flags;

    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        Shader(const Flags & flags);

        void cacheUniforms(const std::vector<std::string>& uniformNames);
        virtual void cacheUniform(const std::string& uniformName) = 0;
        virtual bool hasUniform(const std::string& uniformName) = 0;

        virtual bool upload() = 0;

        virtual bool setUniform(const std::string& uniformName, const bool& value);

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

std::ostream &operator<<(std::ostream &os, PAX::Shader::Flags const &flags);

#endif //PAXENGINE3_SHADER_H
