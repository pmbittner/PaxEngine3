//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLSHADER_H
#define PAXENGINE3_OPENGLSHADER_H

#include <GL/glew.h>
#include <iostream>
#include <map>

#include "../../../include/core/rendering/resource/Shader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLShader : public Shader {
            bool _uploaded = false;

        protected:
            std::string _name, _vertexPath, _fragmentPath;

            GLuint _shaderProgram = -1;
            GLuint _vertexShader = -1;
            GLuint _fragmentShader = -1;

            std::map<std::string, GLint> _uniformLocations;

            static std::string loadCodeFromFile(std::string filename);
            static bool compileShaderAndPrintErrors(GLuint shader);
            static bool setupShaderFromCodeString(GLuint shader, std::string code);

            void insertFlags(std::string& shader, std::string& flags);

        public:
            OpenGLShader(std::string name, std::string vertexPath, std::string fragmentPath, Flags flags = Flags());
            ~OpenGLShader();

            bool loadVertexShaderFromCode(std::string code);
            bool loadFragmentShaderFromCode(std::string code);

            bool linkShader();

            virtual bool upload() override;

            virtual void bind() override;
            virtual void unbind() override;

            virtual void cacheUniform(const std::string& uniformName) override;
            virtual bool hasUniform(const std::string& uniformName) override;

            virtual bool setUniform(const std::string& uniformName, const float& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec2& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec3& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec4& value) override;

            virtual bool setUniform(const std::string& uniformName, const int& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec2& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec3& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec4& value) override;

            virtual bool setUniform(const std::string& uniformName, const glm::mat2& value, bool transpose = false) override;
            virtual bool setUniform(const std::string& uniformName, const glm::mat3& value, bool transpose = false) override;
            virtual bool setUniform(const std::string& uniformName, const glm::mat4& value, bool transpose = false) override;

            GLuint getID();
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADER_H
