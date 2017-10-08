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
        protected:
            std::string _name, _vertexPath, _fragmentPath;

            GLuint _shaderProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::map<std::string, GLint> _uniformLocations;

            static std::string loadCodeFromFile(std::string filename);
            static bool compileShaderAndPrintErrors(GLuint shader);
            static bool setupShaderFromCodeString(GLuint shader, std::string code);

        public:
            OpenGLShader(std::string name, std::string vertexPath, std::string fragmentPath);
            ~OpenGLShader();

            bool loadVertexShaderFromCode(std::string code);
            bool loadFragmentShaderFromCode(std::string code);

            bool linkShader();

            virtual void bind() override;
            virtual void unbind() override;

            virtual void cacheUniform(const std::string& uniformName) override;
            virtual bool hasUniform(const std::string& uniformName) override;

            virtual bool setUniform(const std::string& uniformName, float value) override;
            virtual bool setUniform(const std::string& uniformName, glm::vec2 value) override;
            virtual bool setUniform(const std::string& uniformName, glm::vec3 value) override;
            virtual bool setUniform(const std::string& uniformName, glm::vec4 value) override;

            virtual bool setUniform(const std::string& uniformName, glm::mat3 value) override;
            virtual bool setUniform(const std::string& uniformName, glm::mat4 value) override;

            GLuint getID();
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADER_H
