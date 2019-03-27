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
                // Set by constructor
                size_t elementMemorySize; // sizeof(float)
                int vectorLen = 1;
                GLenum type;
                size_t dataLen = 0;
                std::shared_ptr<void> data;

                VertexAttribute(GLenum type, int vectorLen, size_t elementMemorySize, size_t dataLen, const std::shared_ptr<void> & data)
                : type(type), vectorLen(vectorLen), elementMemorySize(elementMemorySize), dataLen(dataLen), data(data)
                {

                }
            };

        private:
            GLuint _vao, _ibo, _vbo;
            GLenum _faceMode;

            GLsizei _numberOfVertices, _numberOfFaces, _verticesPerFace;
            std::vector<VertexAttribute> attributes;
            std::vector<std::vector<int>> _indices;

            template<typename T>
            void initialize(const std::vector<T> &vertices) {
                _numberOfVertices = static_cast<GLsizei>(vertices.size());
                _numberOfFaces = static_cast<GLsizei>(_indices.size());
                _verticesPerFace = static_cast<GLsizei>(_indices.at(0).size());

                //this->_vertices.resize(size_t(_numberOfVertices));

                if (_numberOfVertices < _verticesPerFace) {
                    throw std::runtime_error("Insufficient number of vertices. At least vertices for one face have to be given");
                }

                Mesh::addAttribute(Mesh::Vertices, vertices);
            }

            void checkAttributeValidity(size_t attribLen);

        public:
            OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<std::vector<int>> &faces, GLenum faceMode = GL_TRIANGLES);
            OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<std::vector<int>> &faces, GLenum faceMode = GL_TRIANGLES);
            OpenGLMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::ivec3> &faces, GLenum faceMode = GL_TRIANGLES);
            OpenGLMesh(const std::vector<glm::vec2> &vertices, const std::vector<glm::ivec3> &faces, GLenum faceMode = GL_TRIANGLES);
            ~OpenGLMesh() override;

            void render(RenderOptions &renderOptions) override;

            void addAttribute(const std::vector<int> &attrib) override;
            void addAttribute(const std::vector<float> &attrib) override;
            void addAttribute(const std::vector<glm::vec2> &attrib) override;
            void addAttribute(const std::vector<glm::vec3> &attrib) override;
            void addAttribute(const std::vector<glm::vec4> &attrib) override;

            void upload() override;

            GLuint getID();
        };
    }
}
#endif //PAXENGINE3_OPENGLMESH_H
