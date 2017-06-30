//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLSHADER_H
#define PAXENGINE3_OPENGLSHADER_H

#include <GL/glew.h>
#include <iostream>

#include "../../../include/core/rendering/resource/Shader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLShader : public Shader {
        protected:
            std::string _name, _vertexPath, _fragmentPath;

            GLuint _shaderProgram;
            GLuint _vertexShader;
            GLuint _fragmentShader;

            static std::string loadCodeFromFile(std::string filename);
            static bool compileShaderAndPrintErrors(GLuint shader);
            static bool setupShaderFromCodeString(GLuint shader, std::string code);

        public:
            OpenGLShader(std::string name, std::string vertexPath, std::string fragmentPath);
            ~OpenGLShader();

            virtual void bind() override;
            virtual void unbind() override;

            bool loadVertexShaderFromCode(std::string code);
            bool loadFragmentShaderFromCode(std::string code);

            bool linkShader();

            GLuint getID();
        };
    }
}

#endif //PAXENGINE3_OPENGLSHADER_H
