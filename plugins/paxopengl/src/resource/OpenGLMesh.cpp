//
// Created by Paul on 30.06.2017.
//

#include <stdexcept>
#include <paxopengl/resource/OpenGLMesh.h>
#include <polypropylene/reflection/Type.h>

namespace PAX {
    namespace OpenGL {
        size_t OpenGLMesh::VertexAttribute::getSizeInBytes() const {
            return dataLen * elementMemorySize;
        }

        GLenum OpenGLMesh::ToGLFaceMode(PAX::Mesh::FaceMode facemode) {
            switch (facemode) {
                case FaceMode::Triangles: {
                    return GL_TRIANGLES;
                }
                case FaceMode::Points: {
                    return GL_POINTS;
                }
                case FaceMode::Lines: {
                    return GL_LINE_LOOP; // GL_LINES
                }
                default: {
                    PAX_THROW_RUNTIME_ERROR("Unsupported FaceMode " << int(facemode) << " given!");
                }
            }
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<std::vector<int>> &faces) : Mesh() {
            this->indices.resize(faces.size());
            for (const std::vector<int> & face : faces) {
                if (face.size() == 3) {
                    this->indices.emplace_back(face[0], face[1], face[2]);
                } else {
                    PAX_THROW_RUNTIME_ERROR("Faces have to be triangulated!");
                }
            }

            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<int>> &faces) : Mesh() {
            this->indices.resize(faces.size());
            for (const std::vector<int> & face : faces) {
                if (face.size() == 3) {
                    this->indices.emplace_back(face[0], face[1], face[2]);
                } else {
                    PAX_THROW_RUNTIME_ERROR("Faces have to be triangulated!");
                }
            }

            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::ivec3> &faces) : Mesh(), indices(faces) {
            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<glm::ivec3> &faces) : Mesh(), indices(faces) {
            initialize(vertices);
        }

        OpenGLMesh::~OpenGLMesh() {
            if (isUploaded()) {
                glDeleteBuffers(1, &_vbo);
                glDeleteBuffers(1, &_ibo);
                glDeleteVertexArrays(1, &_vao);
            }
        }

        void OpenGLMesh::setFaceMode(PAX::Mesh::FaceMode facemode) {
            Mesh::setFaceMode(facemode);
            this->_faceMode = ToGLFaceMode(facemode);
        }

        void OpenGLMesh::render(RenderOptions &renderOptions) {
            glBindVertexArray(_vao);
            glEnableVertexAttribArray(0);

            if (_numberOfFaces > 0) {
                glDrawElements(_faceMode, _numberOfFaces*_verticesPerFace, GL_UNSIGNED_INT, (GLvoid*) 0);
            } else {
                //glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glDrawArrays(_faceMode, 0, GLsizei(_numberOfVertices));
                //glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }

        template<typename T>
        static OpenGLMesh::VertexAttribute createAttribute(Mesh::AttributeName name, const std::vector<T> &attrib, GLenum type) {
            auto * data = new T[attrib.size()];

            for (int i = 0; i < attrib.size(); ++i) {
                data[i] = attrib[i];
            }

            return OpenGLMesh::VertexAttribute(
                    name,
                    type,
                    1,
                    sizeof(T),
                    attrib.size(),
                    std::shared_ptr<void>(data, [](void* data){delete[] static_cast<T*>(data);})
                    );
        }

        template<glm::length_t L, typename T, glm::qualifier Q>
        static OpenGLMesh::VertexAttribute createAttribute(Mesh::AttributeName name, const std::vector<glm::vec<L, T, Q>> &attrib, GLenum type) {
            size_t dataLen = attrib.size() * L;
            auto * data = new T[dataLen];

            for (int i = 0; i < attrib.size(); ++i) {
                for (int component = 0; component < L; ++component) {
                    data[(i*L) + component] = attrib[i][component];
                }
            }

            return OpenGLMesh::VertexAttribute(
                    name,
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

        void OpenGLMesh::addAttribute(Mesh::AttributeName name, const std::vector<int> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(name, attrib, GL_INT));
        }

        void OpenGLMesh::addAttribute(Mesh::AttributeName name, const std::vector<float> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(name, attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(Mesh::AttributeName name, const std::vector<glm::vec2> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(name, attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(Mesh::AttributeName name, const std::vector<glm::vec3> &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(name, attrib, GL_FLOAT));
        }

        void OpenGLMesh::addAttribute(Mesh::AttributeName name, const std::vector< glm::vec4 > &attrib) {
            checkAttributeValidity(attrib.size());
            attributes.emplace_back(createAttribute(name, attrib, GL_FLOAT));
        }

        void OpenGLMesh::uploadNewAttribData(Mesh::AttributeName name, const void * data, size_t dataLenInBytes) const {
            if (isUploaded()) {
                glBindVertexArray(_vao);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo);

                size_t offset = 0;
                size_t i = 0;
                while (attributes[i].name != name) {
                    offset += attributes.at(i).getSizeInBytes();
                    ++i;
                }

                size_t len = attributes.at(i).getSizeInBytes();
                if (len != dataLenInBytes) {
                    PAX_THROW_RUNTIME_ERROR("Size is different!");
                }

                glBufferSubData(GL_ARRAY_BUFFER, offset, len, data);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            } else {
                PAX_NOT_IMPLEMENTED_EXCEPTION();
            }
        }

        void OpenGLMesh::updateAttribute(Mesh::AttributeName name, const std::vector<int> &attrib) {
            uploadNewAttribData(name, attrib.data(), attrib.size() * sizeof(int));
        }

        void OpenGLMesh::updateAttribute(Mesh::AttributeName name, const std::vector<float> &attrib) {
            uploadNewAttribData(name, attrib.data(), attrib.size() * sizeof(float));
        }

        void OpenGLMesh::updateAttribute(Mesh::AttributeName name, const std::vector<glm::vec2> &attrib) {
            uploadNewAttribData(name, attrib.data(), attrib.size() * sizeof(glm::vec2));
        }

        void OpenGLMesh::updateAttribute(Mesh::AttributeName name, const std::vector<glm::vec3> &attrib) {
            uploadNewAttribData(name, attrib.data(), attrib.size() * sizeof(glm::vec3));
        }

        void OpenGLMesh::updateAttribute(Mesh::AttributeName name, const std::vector< glm::vec4 > &attrib) {
            uploadNewAttribData(name, attrib.data(), attrib.size() * sizeof(glm::vec4));
        }

        template<typename T>
        static bool OpenGLMesh_getAttributeTo(const std::vector<OpenGLMesh::VertexAttribute> & attributes, Mesh::AttributeName name, std::vector<T> &data) {
            for (const OpenGLMesh::VertexAttribute & attrib : attributes) {
                if (attrib.name == name) {
                    if (attrib.vectorLen == 1 && attrib.elementMemorySize == sizeof(T)) {
                        data.resize(attrib.dataLen);
                        memcpy(data.data(), attrib.data.get(), attrib.dataLen * sizeof(T));
                        return true;
                    } else {
                        PAX_THROW_RUNTIME_ERROR("Wrong data type \"" << paxtypeid(T).name() << " for attribute " << name << "! Correct would be " << attrib.vectorLen << " * " << attrib.elementMemorySize << "bytes per element.");
                    }
                }
            }

            return false;
        }

        template<glm::length_t L, typename T, glm::qualifier Q>
        static bool OpenGLMesh_getAttributeTo(const std::vector<OpenGLMesh::VertexAttribute> & attributes, Mesh::AttributeName name, std::vector<glm::vec<L, T, Q>> &data) {
            for (const OpenGLMesh::VertexAttribute & attrib : attributes) {
                if (attrib.name == name) {
                    if (attrib.vectorLen == L && attrib.elementMemorySize == sizeof(T)) {
                        data.resize(attrib.dataLen);
                        memcpy(data.data(), attrib.data.get(), attrib.dataLen * sizeof(T));
                        return true;
                    } else {
                        PAX_THROW_RUNTIME_ERROR("Wrong data type \"" << paxtypeid(T).name() << " for attribute " << name << "! Correct would be " << attrib.vectorLen << " * " << attrib.elementMemorySize << "bytes per element.");
                    }
                }
            }

            return false;
        }

        bool OpenGLMesh::getAttribute(AttributeName name, std::vector<int> &data) const {
            if (isUploaded()) return false;
            return OpenGLMesh_getAttributeTo(attributes, name, data);
        }

        bool OpenGLMesh::getAttribute(AttributeName name, std::vector<float> &data) const {
            if (isUploaded()) return false;
            return OpenGLMesh_getAttributeTo(attributes, name, data);
        }

        bool OpenGLMesh::getAttribute(AttributeName name, std::vector<glm::vec2> &data) const {
            if (isUploaded()) return false;
            return OpenGLMesh_getAttributeTo(attributes, name, data);
        }

        bool OpenGLMesh::getAttribute(AttributeName name, std::vector<glm::vec3> &data) const {
            if (isUploaded()) return false;
            return OpenGLMesh_getAttributeTo(attributes, name, data);
        }

        bool OpenGLMesh::getAttribute(AttributeName name, std::vector<glm::vec4> &data) const {
            if (isUploaded()) return false;
            return OpenGLMesh_getAttributeTo(attributes, name, data);
        }

        bool OpenGLMesh::getFaces(std::vector<glm::ivec3> &data) const {
            if (isUploaded()) return false;
            data.resize(indices.size());
            memcpy(data.data(), indices.data(), indices.size() * 3 * sizeof(int));
            return true;
        }

        void OpenGLMesh::upload()
        {
            Mesh::upload();

            /// finalize
            size_t totalBufferLength = 0;
            for (VertexAttribute & attrib : attributes) {
                totalBufferLength += attrib.getSizeInBytes();
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

            std::vector<GLint> indexData(_verticesPerFace*indices.size());

            // create an index array
            for (size_t i = 0; i < indices.size(); i++) {
                for (size_t j= 0; j < _verticesPerFace /*3*/; j++) {
                    indexData[i*_verticesPerFace+j] = indices.at(i)[static_cast<glm::ivec2::length_type>(j)];
                }
            }

            // empty unnecessary vectors
            indices.clear();

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
                offset += attrib.getSizeInBytes();
            }

            if (_numberOfFaces > 0) {
                //create an index buffer
                glGenBuffers(1, &_ibo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

                //upload the index data to OpenGL
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfFaces * _verticesPerFace * sizeof(GLint),
                             indexData.data(), GL_STATIC_DRAW);
            }

            //unbind buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        bool OpenGLMesh::hasAttribute(AttributeName attribName) {
            for (VertexAttribute & v : attributes) {
                if (v.name == attribName)
                    return true;
            }

            return false;
        }

        int OpenGLMesh::getAttributeLocation(AttributeName attribName) {
            int i = 0;
            for (VertexAttribute & v : attributes) {
                if (v.name == attribName)
                    return i;
                ++i;
            }

            return -1;
        }

        GLuint OpenGLMesh::getID() {
            return _vao;
        }
    }
}