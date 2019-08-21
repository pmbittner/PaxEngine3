//
// Created by Paul on 30.06.2017.
//

#include <iomanip>
#include "paxopengl/OpenGLMacros.h"
#include <glm/gtc/type_ptr.hpp>
#include <paxutil/log/Log.h>
#include <sstream>
#include <fstream>
#include "paxopengl/resource/OpenGLShader.h"

#include "paxopengl/OpenGLError.h"

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
            if (logLength > 0) {
                PAX_LOG_RAW(Log::Level::Error, "Shader Compilation - Compiler log:\n------------------\n" << log <<  "==================");
            }
            delete[] log;

            return !hasErrors;
        }

        bool OpenGLShader::setupShaderFromCodeString(GLuint shader, const std::string & code) {
            const char* shader_src = code.c_str();
            glShaderSource(shader,1,&shader_src, NULL);

            bool compiled = compileShaderAndPrintErrors(shader);
            /*
            if (!compiled) {
                PAX_LOG_RAW(Log::Level::Error, "Shader Compilation - Error - Code was:");

                std::stringstream ss(code);
                std::string line;
                int i = 0;
                while (std::getline(ss, line, '\n')) {
                    PAX_LOG_RAW(Log::Level::Error, std::setw(3) << std::fixed << i << "| " << line);
                    ++i;
                }
            }//*/

            return compiled;
        }

        std::string OpenGLShader::loadCodeFromFile(const std::string & filename)
        {
            std::string code;

            std::ifstream codeFile;
            codeFile.open(filename);
            if (!codeFile.is_open()) {
                PAX_LOG(Log::Level::Error, "Unable to open shader file [ " << filename << " ] ");
                throw std::runtime_error("Unable to open shader file " + filename);
            }


            std::string line;
            while (std::getline(codeFile,line)) {
                code+=line+"\n";
            }
            codeFile.close();

            return code;
        }

        void OpenGLShader::insertFlags(std::string& shader, const std::string& flags) {
            std::size_t foundversion = shader.find("#version");

            if (foundversion != std::string::npos) {
                std::size_t foundendline = shader.find("\n", foundversion);
                std::string flagsWithLinebreak = "\n" + flags;

                shader.replace(foundendline, 0, flagsWithLinebreak);
            }
            else {
                PAX_LOG(Log::Level::Error, "Version info in shader required: #version xxx");
            }
        }


        OpenGLShader::OpenGLShader(
                const std::string & name,
                const FileInfo & fileInfo,
                const Flags & flags)
                : Shader(fileInfo, flags), _name(name) {
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
                {
                    std::string vertexCode = loadCodeFromFile(_fileInfo.VertexPath);
                    insertFlags(vertexCode, _flags.VertexFlags);

                    if (!loadShaderFromCode(GL_VERTEX_SHADER, vertexCode, _vertexShader)) {
                        PAX_LOG(Log::Level::Error, "Shader Compilation - Invalid vertex file: " << _fileInfo.VertexPath);
                        return false;
                    }
                }

                {
                    std::string fragmentCode = loadCodeFromFile(_fileInfo.FragmentPath);
                    insertFlags(fragmentCode, _flags.FragmentFlags);

                    if (!loadShaderFromCode(GL_FRAGMENT_SHADER, fragmentCode, _fragmentShader)) {
                        PAX_LOG(Log::Level::Error, "Shader Compilation - Invalid fragment file: " << _fileInfo.FragmentPath);
                        return false;
                    }
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

        bool OpenGLShader::loadShaderFromCode(GLenum type, const std::string & code, GLuint& out_id) {
            if (out_id == 0) {
                out_id = glCreateShader(type);
            }
            //Compile Shader
            bool result = setupShaderFromCodeString(out_id, code);
            /*if (!result) {
                PAX_LOG_RAW(Log::Level::Error, "Shader Compilation - Error in file: " << _name);
            }//*/

            //Attach shader to the program
            glAttachShader(_shaderProgram, out_id);

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
                PAX_LOG_RAW(Log::Level::Info, "Shader Compilation - " << _name << " - Linker log:\n------------------\n" << log << "\n------------------");
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

        void OpenGLShader::detectUniforms() {
            // iterate through all active uniforms
            GLint numUniforms = -1;
            glGetProgramiv(_shaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
            //Log::out.info() << "[OpenGLShader::detectUniforms] Found " << numUniforms << " uniforms in shader " << _name;
            for (int i = 0; i < numUniforms; i++) {

                // get uniform informtion
                GLsizei name_len = -1;
                GLint size = -1;
                GLenum type = GL_ZERO;
                GLchar c_name[100];
                glGetActiveUniform(_shaderProgram, GLuint(i), sizeof(c_name) - 1, &name_len, &size, &type, c_name);
                c_name[name_len] = 0;
                std::string nameS = c_name;

                // check if it's an array
                bool isArray = size > 1;
                if (isArray) {
                    std::size_t pos = nameS.find_last_of('[');
                    nameS = nameS.substr(0, pos);
                }

                // check single uniform and possible further array indices
                for (int j = 0; j < size; j++) {

                    std::string uniformName = isArray
                                              ? nameS + "[" + std::to_string(j) + "]"
                                              : nameS;

                    // get uniform location
                    GLint location = glGetUniformLocation(_shaderProgram, uniformName.c_str());

                    // check if uniform location is valid
                    if (location > -1) {

                        // store uniform type
                        //uniformTypes[uniformName] = type;

                        // store uniform location
                        //Log::out.info() << "[OpenGLShader::detectUniforms]     Found " << uniformName << " at " << location;
                        _uniformLocations[uniformName] = location;
                    }

                        // stop for-loop if invalid index was found
                    else
                        break;
                }
            }

        /*
            if (!hasUniform(uniformName)) {
                GLint location = glGetUniformLocation(_shaderProgram, uniformName.c_str());
                if (PAX_OPENGL_doesUniformExist(location)) {
                    _uniformLocations[uniformName] = location;
                }
            }
            */
        }

        bool OpenGLShader::hasUniform(const std::string &uniformName) {
            return _uniformLocations.find(uniformName) != _uniformLocations.end();
        }

#define PAX_OPENGL_LOADUNIFORM(funcname, ...) \
        if (hasUniform(uniformName)) { \
            funcname(_uniformLocations[uniformName], __VA_ARGS__); \
            return true; \
        } else { /*Log::out.warn() << "The uniform " << uniformName << " does not exist!" << std::endl;*/ } \
        return false;

        bool OpenGLShader::setUniform(const std::string &uniformName, bool value) {
            PAX_OPENGL_LOADUNIFORM(glUniform1f, value)
        }

        bool OpenGLShader::setUniform(const std::string &uniformName, float value) {
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

        bool OpenGLShader::setUniform(const std::string &uniformName, int value) {
            PAX_OPENGL_LOADUNIFORM(glUniform1i, value)
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