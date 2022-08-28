//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLSHADER_H
#define PAXENGINE3_OPENGLSHADER_H

#include <GL/glew.h>
#include <iostream>
#include <map>

#include <paxcore/rendering/data/Shader.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLShader : public Shader {
            struct UniformInfo {
                GLint location;
                GLint size;
                GLenum type;
            };

            struct ShaderProgram {
                bool uploaded = false;
                std::string name;
                bool hasId;
                bool hasVertexShaderId;
                bool hasFragmentShaderId;
                GLuint id = 0;
                GLuint vertexShaderId = 0;
                GLuint fragmentShaderId = 0;
                std::map<std::string, UniformInfo> uniforms;

                explicit ShaderProgram(const std::string & name);
                void init();
                void deleteGPUContent();
                void copyUniformsTo(const ShaderProgram & other);
            } shaderProgram;

        protected:
            static std::string LoadCodeFromFile(const Path & filename, const std::vector<Path> & alreadyIncludedFiles);
            static bool LoadShaderFromCode(GLenum type, const std::string & code, const ShaderProgram & program, GLuint& out_id);
            static bool CompileShaderAndPrintErrors(GLuint shader);
            static bool SetupShaderFromCodeString(GLuint shader, const std::string & code);
            static void InsertFlags(std::string& shader, const std::string& flags);
            static bool Link(ShaderProgram & program);
            static bool Finalize(ShaderProgram & program, const Flags & flags, const FileInfo & fileInfo);
            static void DetectUniforms(ShaderProgram & program);

            bool upload() override;
            void detectUniforms() override;

        public:
            OpenGLShader(const std::string & name, const FileInfo& fileInfo, const Flags & flags = Flags());
            ~OpenGLShader() override;

            void hotreload() override;

            void bind() override;
            void unbind() override;

            bool hasUniform(const std::string& uniformName) override;

            bool setUniform(const std::string& uniformName, bool value) override;

            bool setUniform(const std::string& uniformName, float value) override;
            bool setUniform(const std::string& uniformName, const glm::vec2& value) override;
            bool setUniform(const std::string& uniformName, const glm::vec3& value) override;
            bool setUniform(const std::string& uniformName, const glm::vec4& value) override;

            bool setUniform(const std::string& uniformName, int value) override;
            bool setUniform(const std::string& uniformName, const glm::ivec2& value) override;
            bool setUniform(const std::string& uniformName, const glm::ivec3& value) override;
            bool setUniform(const std::string& uniformName, const glm::ivec4& value) override;

            bool setUniform(const std::string& uniformName, const glm::mat2& value, bool transpose) override;
            bool setUniform(const std::string& uniformName, const glm::mat3& value, bool transpose) override;
            bool setUniform(const std::string& uniformName, const glm::mat4& value, bool transpose) override;

//            PAX_NODISCARD GLuint getID() const;
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADER_H
