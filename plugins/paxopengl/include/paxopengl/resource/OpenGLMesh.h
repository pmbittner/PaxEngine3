//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLMESH_H
#define PAXENGINE3_OPENGLMESH_H

#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <paxcore/rendering/data/Mesh.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLMesh : public Mesh {
        public:
            struct VertexAttribute {
                Mesh::AttributeName name;
                // Set by constructor
                size_t elementMemorySize; // sizeof(float) or sizeof(int)
                int vectorLen = 1; // number of entries in vector (2 for glm::vec2, 3 for glm::vec3, ...)
                GLenum type;
                size_t dataLen = 0; // number of total entries, i.e. vectorLen * vertexCount.
                std::shared_ptr<void> data;

                VertexAttribute(AttributeName name, GLenum type, int vectorLen, size_t elementMemorySize, size_t dataLen, const std::shared_ptr<void> & data)
                : name(name), type(type), vectorLen(vectorLen), elementMemorySize(elementMemorySize), dataLen(dataLen), data(data)
                {

                }

                size_t getSizeInBytes() const;
            };

            static GLenum ToGLFaceMode(FaceMode facemode);

        private:
            GLuint _vao, _ibo, _vbo;
            GLenum _faceMode = GL_TRIANGLES;

            GLsizei _numberOfVertices, _numberOfFaces, _verticesPerFace;
            std::vector<VertexAttribute> attributes;
            std::vector<glm::ivec3> indices;

            template<typename T>
            void initialize(const std::vector<T> &vertices) {
                _numberOfVertices = static_cast<GLsizei>(vertices.size());
                _numberOfFaces    = static_cast<GLsizei>(indices.size());

                if (_numberOfFaces > 0) {
                    _verticesPerFace = 3;
                } else {
                    _verticesPerFace = 0;
                }

                //this->_vertices.resize(size_t(_numberOfVertices));

                if (_numberOfVertices < _verticesPerFace) {
                    PAX_THROW_RUNTIME_ERROR("Insufficient number of vertices: Vertices for at least one face have to be given!");
                }

                addAttribute(Mesh::Vertices, vertices);
            }

            void checkAttributeValidity(size_t attribLen);
            void uploadNewAttribData(Mesh::AttributeName name, const void * data, size_t dataLenInBytes) const;

        public:
            OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<std::vector<int>> &faces);
            OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<int>> &faces);
            OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::ivec3> &faces);
            OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<glm::ivec3> &faces);
            ~OpenGLMesh() override;

            void render(RenderOptions &renderOptions) override;

            void addAttribute(AttributeName name, const std::vector<int> &attrib) override;
            void addAttribute(AttributeName name, const std::vector<float> &attrib) override;
            void addAttribute(AttributeName name, const std::vector<glm::vec2> &attrib) override;
            void addAttribute(AttributeName name, const std::vector<glm::vec3> &attrib) override;
            void addAttribute(AttributeName name, const std::vector<glm::vec4> &attrib) override;

            void updateAttribute(AttributeName name, const std::vector<int> &attrib) override;
            void updateAttribute(AttributeName name, const std::vector<float> &attrib) override;
            void updateAttribute(AttributeName name, const std::vector<glm::vec2> &attrib) override;
            void updateAttribute(AttributeName name, const std::vector<glm::vec3> &attrib) override;
            void updateAttribute(AttributeName name, const std::vector<glm::vec4> &attrib) override;

            bool getAttribute(AttributeName name, std::vector<int> & data) const override;
            bool getAttribute(AttributeName name, std::vector<float> & data) const override;
            bool getAttribute(AttributeName name, std::vector<glm::vec2> & data) const override;
            bool getAttribute(AttributeName name, std::vector<glm::vec3> & data) const override;
            bool getAttribute(AttributeName name, std::vector<glm::vec4> & data) const override;

            bool getFaces(std::vector<glm::ivec3> & data) const override;

            void setFaceMode(FaceMode facemode) override;

            bool hasAttribute(AttributeName attribName) override;
            int getAttributeLocation(AttributeName attribName) override;

            void upload() override;

            GLuint getID();
        };
    }
}
#endif //PAXENGINE3_OPENGLMESH_H
