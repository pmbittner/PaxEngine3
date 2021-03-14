//
// Created by Paul on 30.06.2017.
//

#include "paxopengl/OpenGLMacros.h"
#include <glm/gtc/type_ptr.hpp>
#include <polypropylene/log/Log.h>
#include <sstream>
#include <fstream>
#include "paxopengl/resource/OpenGLShader.h"

#include "paxopengl/OpenGLError.h"

namespace PAX {
    namespace OpenGL {
        bool OpenGLShader::CompileShaderAndPrintErrors(GLuint shader) {
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

        bool OpenGLShader::SetupShaderFromCodeString(GLuint shader, const std::string & code) {
            const char* shader_src = code.c_str();
            glShaderSource(shader,1,&shader_src, NULL);

            bool compiled = CompileShaderAndPrintErrors(shader);
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

        std::string OpenGLShader::LoadCodeFromFile(const std::string & filename)
        {
            std::string code;

            std::ifstream codeFile;
            codeFile.open(filename);
            if (!codeFile.is_open()) {
                PAX_THROW_RUNTIME_ERROR("Unable to open shader file \"" << filename << "\"!");
            }

            std::string line;
            while (std::getline(codeFile,line)) {
                code+=line+"\n";
            }
            codeFile.close();

            return code;
        }

        void OpenGLShader::InsertFlags(std::string& shader, const std::string& flags) {
            std::size_t foundversion = shader.find("#version");

            if (foundversion != std::string::npos) {
                std::size_t foundendline = shader.find('\n', foundversion);
                std::string flagsWithLinebreak = "\n" + flags;

                shader.replace(foundendline, 0, flagsWithLinebreak);
            }
            else {
                PAX_LOG(Log::Level::Error, "Version info in shader required: #version xxx");
            }
        }

        bool OpenGLShader::LoadShaderFromCode(GLenum type, const std::string & code, const ShaderProgram & program, GLuint& out_id) {
            if (out_id == 0) {
                out_id = glCreateShader(type);
            }
            //Compile Shader
            bool result = SetupShaderFromCodeString(out_id, code);
            /*if (!result) {
                PAX_LOG_RAW(Log::Level::Error, "Shader Compilation - Error in file: " << _name);
            }//*/

            //Attach shader to the program
            glAttachShader(program.id, out_id);

            return result;
        }

        bool OpenGLShader::Link(ShaderProgram & program) {
            glLinkProgram(program.id);

            // get log //
            int logMaxLength = 0;
            glGetProgramiv(program.id, GL_INFO_LOG_LENGTH, &logMaxLength);
            char* log = new char[logMaxLength]();
            int logLength = 0;
            glGetProgramInfoLog(program.id, logMaxLength, &logLength, log);

            if (logLength > 0) {
                PAX_LOG_RAW(Log::Level::Info, "Shader Compilation - " << program.name << " - Linker log:\n------------------\n" << log << "\n------------------");
                return false;
            }

            delete[] log;
            return true;
        }

        bool OpenGLShader::Finalize(ShaderProgram &program, const Flags & flags, const FileInfo & fileInfo) {
            if (!program.uploaded) {
                {
                    std::string vertexCode = LoadCodeFromFile(fileInfo.VertexPath);
                    InsertFlags(vertexCode, flags.VertexFlags);

                    if (!LoadShaderFromCode(GL_VERTEX_SHADER, vertexCode, program, program.vertexShaderId)) {
                        PAX_LOG(Log::Level::Error, "Shader Compilation - Invalid vertex file: " << fileInfo.VertexPath);
                        return false;
                    }
                    program.hasVertexShaderId = true;
                }

                {
                    std::string fragmentCode = LoadCodeFromFile(fileInfo.FragmentPath);
                    InsertFlags(fragmentCode, flags.FragmentFlags);

                    if (!LoadShaderFromCode(GL_FRAGMENT_SHADER, fragmentCode, program, program.fragmentShaderId)) {
                        PAX_LOG(Log::Level::Error, "Shader Compilation - Invalid fragment file: " << fileInfo.FragmentPath);
                        return false;
                    }
                    program.hasFragmentShaderId = true;
                }

                glBindAttribLocation(program.id, 0, "position");
                if (Link(program)) {
                    glBindFragDataLocation(program.id, 0, "out_Color");
                } else {
                    return false;
                }

//                flags.reset();
                program.uploaded = true;
            }

            return true;
        }

        void OpenGLShader::DetectUniforms(ShaderProgram & program) {
            program.uniforms.clear();

            // iterate through all active uniforms
            GLint numUniforms = -1;
            glGetProgramiv(program.id, GL_ACTIVE_UNIFORMS, &numUniforms);
            //Log::out.info() << "[OpenGLShader::detectUniforms] Found " << numUniforms << " uniforms in shader " << _name;
            for (int i = 0; i < numUniforms; i++) {
                // get uniform informtion
                GLsizei name_len = -1;
                GLint size = -1;
                GLenum type = GL_ZERO;
                GLchar c_name[100];
                glGetActiveUniform(program.id, GLuint(i), sizeof(c_name) - 1, &name_len, &size, &type, c_name);
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
                    std::string uniformName = nameS;

                    if (isArray) {
                        uniformName = nameS + "[" + std::to_string(j) + "]";
                    }

                    UniformInfo uniformInfo{};
                    uniformInfo.size = size;
                    uniformInfo.type = type;
                    uniformInfo.location = glGetUniformLocation(program.id, uniformName.c_str());

                    // check if uniform location is valid
                    if (uniformInfo.location > -1) {

                        // store uniform type
                        //uniformTypes[uniformName] = type;

                        // store uniform location
                        //Log::out.info() << "[OpenGLShader::detectUniforms]     Found " << uniformName << " at " << location;
                        program.uniforms[uniformName] = uniformInfo;
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

        OpenGLShader::ShaderProgram::ShaderProgram(const std::string & name) :
        uploaded(false),
        id(0),
        vertexShaderId(0),
        fragmentShaderId(0),
        hasId(false),
        hasVertexShaderId(false),
        hasFragmentShaderId(false)
        {}

        void OpenGLShader::ShaderProgram::init() {
            id = glCreateProgram();
            hasId = true;
        }

        void OpenGLShader::ShaderProgram::deleteGPUContent() {
            if (hasId) {
                if (hasVertexShaderId) {
                    glDetachShader(id, vertexShaderId);
                    glDeleteShader(vertexShaderId);
                    vertexShaderId = 0;
                    hasVertexShaderId = false;
                }
                if (hasFragmentShaderId) {
                    glDetachShader(id, fragmentShaderId);
                    glDeleteShader(fragmentShaderId);
                    fragmentShaderId = 0;
                    hasFragmentShaderId = false;
                }
                glDeleteProgram(id);
                hasId = false;
                id = 0;
            }

            uploaded = false;
        }

        OpenGLShader::OpenGLShader(
                const std::string & name,
                const FileInfo & fileInfo,
                const Flags & flags)
                : Shader(fileInfo, flags), shaderProgram(name) {}

        OpenGLShader::~OpenGLShader() {
            shaderProgram.deleteGPUContent();
        }

        bool OpenGLShader::upload() {
            shaderProgram.init();
            return Finalize(shaderProgram, _flags, _fileInfo);
        }

        void OpenGLShader::detectUniforms() {
            DetectUniforms(shaderProgram);
        }

        void OpenGLShader::bind() {
            glUseProgram(shaderProgram.id);
        }

        void OpenGLShader::unbind() {
            glUseProgram(0);
        }

//        GLuint OpenGLShader::getID() const {
//            return shaderProgram.id;
//        }

        void OpenGLShader::ShaderProgram::copyUniformsTo(const ShaderProgram &other) {
            for (const auto& uniformEntryOfSource : uniforms) {
                const auto & uniformEntryOfTarget = other.uniforms.find(uniformEntryOfSource.first);
                if (uniformEntryOfTarget != other.uniforms.end()) {
                    const UniformInfo & uniformInSource = uniformEntryOfSource.second;
                    const UniformInfo & uniformInTarget = uniformEntryOfTarget->second;
                    if (uniformInTarget.type == uniformInSource.type && uniformInTarget.size == uniformInSource.size) {
#define PAXGL_COPYUNIFORM_GETADDR(val) &val
#define PAXGL_COPYUNIFORM_GETVECBEGIN(val) &val.x
#define PAXGL_COPYUNIFORM_GETMATBEGIN(val) glm::value_ptr(val)
#define PAXGL_COPYUNIFORM_PUT1(val) val
#define PAXGL_COPYUNIFORM_PUT2(val) val.x, val.y
#define PAXGL_COPYUNIFORM_PUT3(val) val.x, val.y, val.z
#define PAXGL_COPYUNIFORM_PUT4(val) val.x, val.y, val.z, val.w
#define PAXGL_COPYUNIFORM_PUTMAT(val) 1, false, glm::value_ptr(val)
#define PAXGL_COPYUNIFORM(oldP, newP, oldU, newU, valtype, get, put, GETTER, PUTTER) \
    glUseProgram(oldP.id); \
    valtype val; \
    get(oldP.id, oldU.location, GETTER(val)); \
    glUseProgram(newP.id); \
    put(newU.location, PUTTER(val));
#define PAXGL_COPYUNIFORM_HERE(valtype, get, put, GETTER, PUTTER) PAXGL_COPYUNIFORM((*this), other, uniformInSource, uniformInTarget, valtype, get, put, GETTER, PUTTER)
#define PAXGL_COPYUNIFORM_CASE(argtype, valtype, get, put, GETTER, PUTTER) case argtype: { PAXGL_COPYUNIFORM_HERE(valtype, get, put, GETTER, PUTTER) break;}
#define PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(type, valtypename, vectypename, get, typeShort) \
    PAXGL_COPYUNIFORM_CASE(type, valtypename, get, glUniform##1##typeShort, PAXGL_COPYUNIFORM_GETADDR, PAXGL_COPYUNIFORM_PUT1) \
    PAXGL_COPYUNIFORM_CASE(type##_VEC2, vectypename##2, get, glUniform##2##typeShort, PAXGL_COPYUNIFORM_GETVECBEGIN, PAXGL_COPYUNIFORM_PUT2) \
    PAXGL_COPYUNIFORM_CASE(type##_VEC3, vectypename##3, get, glUniform##3##typeShort, PAXGL_COPYUNIFORM_GETVECBEGIN, PAXGL_COPYUNIFORM_PUT3) \
    PAXGL_COPYUNIFORM_CASE(type##_VEC4, vectypename##4, get, glUniform##4##typeShort, PAXGL_COPYUNIFORM_GETVECBEGIN, PAXGL_COPYUNIFORM_PUT4)
#define PAXGL_COPYUNIFORM_CASES_FOR_ALL_MATS_OF_TYPE(type, mattypename, get, typeShort) \
    PAXGL_COPYUNIFORM_CASE(type##_MAT2, mattypename##2, get, glUniformMatrix##2##typeShort, PAXGL_COPYUNIFORM_GETMATBEGIN, PAXGL_COPYUNIFORM_PUTMAT) \
    PAXGL_COPYUNIFORM_CASE(type##_MAT3, mattypename##3, get, glUniformMatrix##3##typeShort, PAXGL_COPYUNIFORM_GETMATBEGIN, PAXGL_COPYUNIFORM_PUTMAT) \
    PAXGL_COPYUNIFORM_CASE(type##_MAT4, mattypename##4, get, glUniformMatrix##4##typeShort, PAXGL_COPYUNIFORM_GETMATBEGIN, PAXGL_COPYUNIFORM_PUTMAT)

                        switch (uniformInTarget.type) {
                            // To add more types have a look here
                            // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetActiveUniform.xhtml
                            // and here
                            // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetUniform.xhtml

                            // We just treat booleans as floats because there is no proper tool support at the side of OpenGL
                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(GL_BOOL, GLfloat, glm::fvec, glGetUniformfv, f)
                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(GL_FLOAT, GLfloat, glm::vec, glGetUniformfv, f)
                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(GL_DOUBLE, GLdouble, glm::dvec, glGetUniformdv, d)
                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(GL_INT, GLint, glm::ivec, glGetUniformiv, i)
                            // There is not glm::uivec. We have to add it ourselfs with the template.
                            // As uploading unsigned ints is not supported yet, we skip this for now, too.
//                                PAXGL_COPYUNIFORM_CASES_FOR_ALL_DIMENSIONS_OF_TYPE(GL_UNSIGNED_INT, GLuint, glm::uivec, glGetUniformuiv, ui)

                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_MATS_OF_TYPE(GL_FLOAT, glm::mat, glGetUniformfv, fv)
                            PAXGL_COPYUNIFORM_CASES_FOR_ALL_MATS_OF_TYPE(GL_DOUBLE, glm::dmat, glGetUniformdv, dv)
                        }
                        glUseProgram(0);
                    }
                }
            }
        }

        void OpenGLShader::hotreload() {
            ShaderProgram reloadedProgram(shaderProgram.name);
            reloadedProgram.init();
            if (Finalize(reloadedProgram, _flags, _fileInfo)) {
                // compilation was successful
                DetectUniforms(reloadedProgram);
                shaderProgram.copyUniformsTo(reloadedProgram);
                shaderProgram.deleteGPUContent();
                shaderProgram = reloadedProgram;
            } else {
                reloadedProgram.deleteGPUContent();
            }
        }

        bool OpenGLShader::hasUniform(const std::string &uniformName) {
            return shaderProgram.uniforms.find(uniformName) != shaderProgram.uniforms.end();
        }

#define PAX_OPENGL_LOADUNIFORM(funcname, ...) \
        if (hasUniform(uniformName)) { \
            funcname(shaderProgram.uniforms[uniformName].location, __VA_ARGS__); \
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