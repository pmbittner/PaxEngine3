//
// Created by Paul on 30.06.2017.
//

#include <iomanip>
#include "../../../include/opengl/resource/OpenGLShader.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    namespace OpenGL {
        bool OpenGLShader::compileShaderAndPrintErrors(GLuint shader) {
            glCompileShader(shader);

            int logMaxLength;
            int logLength;

            GLint isCompiled = 0;
            glGetShaderiv(shader,GL_COMPILE_STATUS,&isCompiled);


            bool hasErrors = (isCompiled==GL_FALSE);

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logMaxLength);
            char* log = new char[logMaxLength];
            glGetShaderInfoLog(shader,logMaxLength, &logLength, log);
            if (logLength> 0) {
                LOG(INFO) << "Shader Compilation - Compiler log:\n------------------\n" << log <<  "==================";
            }
            delete[] log;

            return !hasErrors;
        }

        bool OpenGLShader::setupShaderFromCodeString(GLuint shader, std::string code) {
            const char* shader_src = code.c_str();
            glShaderSource(shader,1,&shader_src, NULL);

            bool compiled = compileShaderAndPrintErrors(shader);
            if (!compiled) {
                LOG(ERROR) << "Shader Compilation - Error - Code was:";

                std::stringstream ss(code);
                std::string line;
                int i = 0;
                while (std::getline(ss, line, '\n')) {
                    LOG(ERROR) << std::setw(3) << std::fixed << ++i << "| " << line;
                }
            }

            return compiled;
        }

        std::string OpenGLShader::loadCodeFromFile(std::string filename)
        {
            std::string code;

            std::ifstream codeFile;
            codeFile.open(filename);
            if (!codeFile.is_open()) {
                std::cerr << "Unable to open shader file " << filename << std::endl;
                throw std::runtime_error("Unable to open shader file " + filename);
            }


            std::string line;
            while (std::getline(codeFile,line)) {
                code+=line+"\n";
            }
            codeFile.close();

            return code;
        }

        OpenGLShader::OpenGLShader(std::string name, std::string vertexPath, std::string fragmentPath) : _name(name), _vertexPath(vertexPath), _fragmentPath(fragmentPath) {
            _shaderProgram  = glCreateProgram();
            _vertexShader   = 0;
            _fragmentShader = 0;

            if (!loadVertexShaderFromCode(loadCodeFromFile(_vertexPath)))
                LOG(ERROR) << "Shader Compilation - Vertex file: " << _vertexPath;

            if (!loadFragmentShaderFromCode(loadCodeFromFile(_fragmentPath)))
                LOG(ERROR) << "Shader Compilation - Fragment file: " << _fragmentPath;

            glBindAttribLocation(_shaderProgram, 0, "position");
            if (linkShader()) {
                glBindFragDataLocation(_shaderProgram, 0, "out_Color");
            }
        }

        OpenGLShader::~OpenGLShader() {
            glDetachShader(_shaderProgram, _vertexShader);
            glDetachShader(_shaderProgram, _fragmentShader);
            glDeleteShader(_vertexShader);
            glDeleteShader(_fragmentShader);
            glDeleteProgram(_shaderProgram);
        }

        bool OpenGLShader::loadVertexShaderFromCode(std::string code) {
            if (_vertexShader == 0) {
                _vertexShader = glCreateShader(GL_VERTEX_SHADER);
            }
            //Compile Shader
            bool result = setupShaderFromCodeString(_vertexShader,code);
            if (!result) {
                LOG(ERROR) << "Shader Compilation - Invalid vertex shader: " << _name;
            }

            //Attach shader to the program
            glAttachShader(_shaderProgram,_vertexShader);

            return result;
        }

        bool OpenGLShader::loadFragmentShaderFromCode(std::string code) {
            if (_fragmentShader==0) {
                _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            }
            //Compile Shader
            bool result = setupShaderFromCodeString(_fragmentShader,code);
            if (!result) {
                LOG(ERROR) << "Shader Compilation - Invalid fragment shader: " << _name;
            }

            //Attach shader to the program
            glAttachShader(_shaderProgram,_fragmentShader);

            return result;
        }

        bool OpenGLShader::linkShader() {
            glLinkProgram(_shaderProgram);

            // get log //
            int logMaxLength = 0;
            glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &logMaxLength);
            char* log = new char[logMaxLength]();
            int logLength = 0;
            glGetProgramInfoLog(_shaderProgram, logMaxLength, &logLength, log);
            if (logLength > 0) {
                LOG(INFO) << "Shader Compilation - " << _name << " - Linker log:\n------------------\n" << log << "\n------------------";
                return false;
            }
            delete[] log;
            return true;
        }

        void OpenGLShader::bind() {
            glUseProgram(_shaderProgram);
        }

        void OpenGLShader::unbind() {
            glUseProgram(0);
        }

        GLuint OpenGLShader::getID() {
            return _shaderProgram;
        }
    }
}