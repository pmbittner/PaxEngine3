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
            bool _uploaded = false;

        protected:
            std::string _name, _vertexPath, _fragmentPath;

            GLuint _shaderProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::map<std::string, GLint> _uniformLocations;

            static std::string loadCodeFromFile(const std::string & filename);
            static bool compileShaderAndPrintErrors(GLuint shader);
            static bool setupShaderFromCodeString(GLuint shader, const std::string & code);

            void insertFlags(std::string& shader, const std::string& flags);

        public:
            OpenGLShader(const std::string & name, const std::string & vertexPath, const std::string & fragmentPath, const Flags & flags = Flags());
            ~OpenGLShader();

            bool loadVertexShaderFromCode(const std::string & code);
            bool loadFragmentShaderFromCode(const std::string & code);

            bool linkShader();

            virtual bool upload() override;

            virtual void bind() override;
            virtual void unbind() override;

            virtual void cacheUniform(const std::string& uniformName) override;
            virtual bool hasUniform(const std::string& uniformName) override;

            virtual bool setUniform(const std::string& uniformName, const bool& value) override;

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
