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

        private:
            bool loadShaderFromCode(GLenum type, const std::string & code, GLuint& out_id);

        protected:
            std::string _name;

            GLuint _shaderProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            std::map<std::string, GLint> _uniformLocations;

            static std::string loadCodeFromFile(const std::string & filename);
            static bool compileShaderAndPrintErrors(GLuint shader);
            static bool setupShaderFromCodeString(GLuint shader, const std::string & code);

            void insertFlags(std::string& shader, const std::string& flags);

            virtual bool upload() override;
            virtual void detectUniforms() override;

        public:
            OpenGLShader(const std::string & name, const FileInfo& fileInfo, const Flags & flags = Flags());
            ~OpenGLShader();

            bool linkShader();


            virtual void bind() override;
            virtual void unbind() override;

            virtual bool hasUniform(const std::string& uniformName) override;

            virtual bool setUniform(const std::string& uniformName, bool value) override;

            virtual bool setUniform(const std::string& uniformName, float value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec2& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec3& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::vec4& value) override;

            virtual bool setUniform(const std::string& uniformName, int value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec2& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec3& value) override;
            virtual bool setUniform(const std::string& uniformName, const glm::ivec4& value) override;

            virtual bool setUniform(const std::string& uniformName, const glm::mat2& value, bool transpose) override;
            virtual bool setUniform(const std::string& uniformName, const glm::mat3& value, bool transpose) override;
            virtual bool setUniform(const std::string& uniformName, const glm::mat4& value, bool transpose) override;

            GLuint getID();
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADER_H
