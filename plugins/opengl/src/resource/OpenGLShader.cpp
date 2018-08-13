//
// Created by Paul on 30.06.2017.
//

#include <iomanip>
#include <easylogging++.h>
#include <OpenGLMacros.h>
#include <glm/gtc/type_ptr.hpp>
#include <resource/OpenGLShader.h>

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

        void OpenGLShader::insertFlags(std::string& shader, std::string& flags) {
            std::size_t foundversion = shader.find("#version");

            if (foundversion != std::string::npos) {
                std::size_t foundendline = shader.find("\n", foundversion);
                std::string flagsWithLinebreak = "\n" + flags;

                shader.replace(foundendline, 0, flagsWithLinebreak);
            }
            else {
                LOG(ERROR) << "Version info in shader required: #version xxx";
            }
        }


        OpenGLShader::OpenGLShader(std::string name, std::string vertexPath, std::string fragmentPath, Flags flags) : Shader(flags), _name(name), _vertexPath(vertexPath), _fragmentPath(fragmentPath) {
            _shaderProgram  = glCreateProgram();
            _vertexShader   = 0;
            _fragmentShader = 0;
        }

        OpenGLShader::~OpenGLShader() {
            glDetachShader(_shaderProgram, _vertexShader);
            glDetachShader(_shaderProgram, _fragmentShader);
            glDeleteShader(_vertexShader);
            glDeleteShader(_fragmentShader);
            glDeleteProgram(_shaderProgram);
        }

        bool OpenGLShader::upload() {
            if (!_uploaded) {
                std::string vertexCode = loadCodeFromFile(_vertexPath);
                insertFlags(vertexCode, _flags.VertexFlags);

                if (!loadVertexShaderFromCode(vertexCode)) {
                    LOG(ERROR) << "Shader Compilation - Vertex file: " << _vertexPath;
                    return false;
                }

                std::string fragmentCode = loadCodeFromFile(_fragmentPath);
                insertFlags(fragmentCode, _flags.FragmentFlags);

                if (!loadFragmentShaderFromCode(fragmentCode)) {
                    LOG(ERROR) << "Shader Compilation - Fragment file: " << _fragmentPath;
                    return false;
                }

                glBindAttribLocation(_shaderProgram, 0, "position");
                if (linkShader()) {
                    glBindFragDataLocation(_shaderProgram, 0, "out_Color");
                }

                _flags.reset();
                _uploaded = true;
            }

            return true;
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

        void OpenGLShader::cacheUniform(const std::string &uniformName) {
            if (!hasUniform(uniformName)) {
                GLint location = glGetUniformLocation(_shaderProgram, uniformName.c_str());
                if (PAX_OPENGL_doesUniformExist(location)) {
                    _uniformLocations[uniformName] = location;
                }
            }
        }

        bool OpenGLShader::hasUniform(const std::string &uniformName) {
            return _uniformLocations.find(uniformName) != _uniformLocations.end();
        }

#define PAX_OPENGL_LOADUNIFORM(funcname, ...) \
        if (hasUniform(uniformName)) { \
            funcname(_uniformLocations[uniformName], __VA_ARGS__); \
            return true; \
        } \
        return false;

        bool OpenGLShader::setUniform(const std::string &uniformName, const float& value) {
            PAX_OPENGL_LOADUNIFORM(glUniform1f, value)
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::vec2& value) {
            PAX_OPENGL_LOADUNIFORM(glUniform2f, value.x, value.y)
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::vec3& value) {
            PAX_OPENGL_LOADUNIFORM(glUniform3f, value.x, value.y, value.z)
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::vec4& value) {
            PAX_OPENGL_LOADUNIFORM(glUniform4f, value.x, value.y, value.z, value.w)
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const int &value) {
            PAX_OPENGL_LOADUNIFORM(glUniform1i, value);
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::ivec2 &value) {
            PAX_OPENGL_LOADUNIFORM(glUniform2i, value.x, value.y);
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::ivec3 &value) {
            PAX_OPENGL_LOADUNIFORM(glUniform3i, value.x, value.y, value.z);
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::ivec4 &value) {
            PAX_OPENGL_LOADUNIFORM(glUniform4i, value.x, value.y, value.z, value.w);
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::mat2 &value, bool transpose) {
            PAX_OPENGL_LOADUNIFORM(glUniformMatrix2fv, 1, transpose, glm::value_ptr(value))
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::mat3& value, bool transpose) {
            PAX_OPENGL_LOADUNIFORM(glUniformMatrix3fv, 1, transpose, glm::value_ptr(value))
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, const glm::mat4& value, bool transpose) {
            PAX_OPENGL_LOADUNIFORM(glUniformMatrix4fv, 1, transpose, glm::value_ptr(value))
        }

#undef PAX_OPENGL_LOADUNIFORM
    }
}