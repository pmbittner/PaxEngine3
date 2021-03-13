//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_SHADER_H
#define PAXENGINE3_SHADER_H

#include <string>
#include <vector>

#include <paxutil/lib/GlmIncludes.h>
#include <polypropylene/io/Path.h>

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

        struct FileInfo {
            Path VertexPath;
            Path GeometryPath;
            Path FragmentPath;
            Path TessControlPath;
            Path TessEvaluationPath;
            Path ComputePath;

            FileInfo();
            FileInfo(const Path& vertexPath, const Path& fragmentPath);
            bool operator==(const FileInfo& other) const;
        };

    protected:
        FileInfo _fileInfo;
        Flags _flags;

        virtual void detectUniforms() = 0;
        virtual bool upload() = 0;

    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        Shader(const FileInfo& fileInfo, const Flags & flags);
        virtual ~Shader() = 0;

        virtual void initialize();

        virtual void hotreload() = 0;

        PAX_NODISCARD const FileInfo & getFileInfo() const;

        virtual bool hasUniform(const std::string& uniformName) = 0;

        virtual bool setUniform(const std::string& uniformName, bool value);

        virtual bool setUniform(const std::string& uniformName, float value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec2& value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec3& value);
        virtual bool setUniform(const std::string& uniformName, const glm::vec4& value);

        virtual bool setUniform(const std::string& uniformName, int value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec2& value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec3& value);
        virtual bool setUniform(const std::string& uniformName, const glm::ivec4& value);

        virtual bool setUniform(const std::string& uniformName, const glm::mat2& value, bool transpose);
        virtual bool setUniform(const std::string& uniformName, const glm::mat3& value, bool transpose);
        virtual bool setUniform(const std::string& uniformName, const glm::mat4& value, bool transpose);
    };
}

#include <paxcore/OStreamOverloads.h>

#endif //PAXENGINE3_SHADER_H
