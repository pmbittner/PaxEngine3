//
// Created by Paul on 30.06.2017.
//

#include <stdexcept>
#include "paxopengl/resource/OpenGLMesh.h"

namespace PAX {
    namespace OpenGL {
        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<std::vector<int>> &faces, GLenum faceMode) : _faceMode(faceMode), _indices(faces) {
            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<int>> &faces, GLenum faceMode) : _faceMode(faceMode), _indices(faces) {
            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::ivec3> &faces, GLenum faceMode) : _faceMode(faceMode) {
            for (const glm::ivec3& triangle : faces)
                _indices.push_back({triangle.x, triangle.y, triangle.z});
            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<glm::ivec3> &faces, GLenum faceMode) : _faceMode(faceMode) {
            for (const glm::ivec3& triangle : faces)
                _indices.push_back({triangle.x, triangle.y, triangle.z});
            initialize(vertices);
        }

        OpenGLMesh::~OpenGLMesh() {
            if (isUploaded()) {
                glDeleteBuffers(1, &_vbo);
                glDeleteBuffers(1, &_ibo);
                glDeleteVertexArrays(1, &_vao);
            }
        }

        void OpenGLMesh::render(RenderOptions &renderOptions) {
            glBindVertexArray(_vao);
            glEnableVertexAttribArray(0);
            glDrawElements(_faceMode, _numberOfFaces*_verticesPerFace, GL_UNSIGNED_INT, (GLvoid*) 0);
            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }

        template<typename T>
        static OpenGLMesh::VertexAttribute createAttribute(const std::vector<T> &attrib, GLenum type) {
            auto * data = new T[attrib.size()];

            for (int i = 0; i < attrib.size(); ++i) {
                data[i] = attrib[i];
            }

            return OpenGLMesh::VertexAttribute(
                    type,
                    1,
                    sizeof(T),
                    attrib.size(),
                    std::shared_ptr<void>(data, [](void* data){delete[] static_cast<T*>(data);})
                    );
        }

        template<glm::length_t L, typename T, glm::qualifier Q>
        static OpenGLMesh::VertexAttribute createAttribute(const std::vector<glm::vec<L, T, Q>> &attrib, GLenum type) {
            size_t dataLen = attrib.size() * L;
            auto * data = new T[dataLen];

            for (int i = 0; i < attrib.size(); ++i) {
                for (int component = 0; component < L; ++component) {
                    data[(i*L) + component] = attrib[i][component];
                }
            }

            return OpenGLMesh::VertexAttribute(
                    type,
                    L,
                    sizeof(T),
                    dataLen,
                    std::shared_ptr<void>(data, [](void* data){delete[] static_cast<T*>(data);})
                    );
        }

        void OpenGLMesh::checkAttributeValidity(size_t attribLen) {
            //check if this object was finalized
            if (isUploaded()) {
                PAX_THROW_RUNTIME_ERROR("Trying to add attributes to finalized OGLObject");
            }

            //make sure that an attribute is given for all vertices
            if (attribLen != _numberOfVertices) {
                PAX_THROW_RUNTIME_ERROR("Number of attributes("+std::to_string(attribLen)+") does not match the number of vertices("+std::to_string(_numberOfVertices)+")");
            }
        }

        void OpenGLMesh::addAttribute(const std::vector<int> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(attrib, GL_INT));
        }

        void OpenGLMesh::addAttribute(const std::vector<float> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(const std::vector<glm::vec2> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(const std::vector<glm::vec3> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(const std::vector< glm::vec4 > &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(attrib, GL_FLOAT));
        }

        void OpenGLMesh::upload()
        {
            Mesh::upload();

            /// finalize
            size_t totalBufferLength = 0;
            for (VertexAttribute & attrib : attributes) {
                totalBufferLength += attrib.dataLen * attrib.elementMemorySize;
            }

            std::vector<char> vertexData(totalBufferLength);
            {
                size_t offset = 0;
                for (VertexAttribute & attrib : attributes) {
                    size_t len = attrib.dataLen * attrib.elementMemorySize;
                    char* data = static_cast<char*>(attrib.data.get());
                    for (size_t i = 0; i < len; ++i) {
                        vertexData[i + offset] = data[i];
                    }

                    offset += len;
                }
            }

            std::vector<GLint> indexData(_verticesPerFace*_indices.size());

            //create an index array
            for (size_t i = 0; i < _indices.size(); i++) {
                for (size_t j= 0; j < _verticesPerFace; j++) {
                    indexData[i*_verticesPerFace+j] = _indices.at(i).at(j);
                }
            }

            // empty unnecessary vectors
            _indices.clear();

            /// upload

            //create a Vertex Array Object
            glGenVertexArrays(1, &_vao);
            glBindVertexArray(_vao);

            //create a Vertex Buffer Object
            glGenBuffers(1,&_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);

            // upload data to OpenGL
            glBufferData(GL_ARRAY_BUFFER, totalBufferLength * sizeof(char), vertexData.data(), GL_STATIC_DRAW);
            //define and enable the vertex attribute pointers
            GLuint index = 0;
            size_t offset = 0;
            for (VertexAttribute & attrib : attributes) {
                glVertexAttribPointer(index, attrib.vectorLen, attrib.type, GL_FALSE, 0, reinterpret_cast<GLvoid*>(offset));
                glEnableVertexAttribArray(index);
                ++index;
                offset += attrib.dataLen * attrib.elementMemorySize;
            }


            //create an index buffer
            glGenBuffers(1,&_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

            //upload the index data to OpenGL
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfFaces*_verticesPerFace* sizeof(GLint), indexData.data(), GL_STATIC_DRAW);

            //unbind buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        GLuint OpenGLMesh::getID() {
            return _vao;
        }
    }
}