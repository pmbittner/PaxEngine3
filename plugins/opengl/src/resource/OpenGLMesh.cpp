//
// Created by Paul on 30.06.2017.
//

#include <stdexcept>
#include <easylogging++.h>
#include <resource/OpenGLMesh.h>

namespace PAX {
    namespace OpenGL {
        OpenGLMesh::OpenGLMesh(std::vector<glm::vec3> &vertices, std::vector<std::vector<int>> &faces, GLenum faceMode) : _faceMode(faceMode), _indices(faces) {
            initialize(vertices);
        }

        OpenGLMesh::OpenGLMesh(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> &faces, GLenum faceMode) : _faceMode(faceMode) {
            for (glm::ivec3& triangle : faces)
                _indices.push_back({triangle.x, triangle.y, triangle.z});
            initialize(vertices);
        }

        void OpenGLMesh::initialize(std::vector<glm::vec3> &vertices) {
            _numberOfVertices = static_cast<GLsizei>(vertices.size());
            _numberOfFaces = static_cast<GLsizei>(_indices.size());
            _verticesPerFace = static_cast<GLsizei>(_indices.at(0).size());

            this->_vertices.resize(size_t(_numberOfVertices));

            if (_numberOfVertices < _verticesPerFace) {
                throw std::runtime_error("Insufficient number of vertices. At least vertices for one face have to be given");
            }

            Mesh::addAttribute(Mesh::Vertices, vertices);
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

        void OpenGLMesh::addAttribute(const std::vector<float> &attrib)
        {
            //check if this object was finalized
            if (isUploaded()) {
                throw std::runtime_error("Trying to add _attributes to finalized OGLObject");
            }

            //make sure that an attribute is given for all vertices
            if (attrib.size() != _numberOfVertices) {
                throw std::runtime_error("Number of _attributes("+std::to_string(attrib.size())+") does not match the number of vertices("+std::to_string(_numberOfVertices)+")");
            }

            //update offset index
            _attributes.emplace_back(std::pair<int,int>(_currentOffset,1));
            _currentOffset += 1;

            //add the attribute at the end of each vertex
            for (size_t i = 0; i < _vertices.size(); i++) {
                _vertices.at(i).push_back(attrib.at(i));
            }
        }


        void OpenGLMesh::addAttribute(const std::vector<glm::vec2> &attrib)
        {
            //check if this object was finalized
            if (isUploaded()) {
                throw std::runtime_error("Trying to add _attributes to finalized OGLObject");
            }

            //make sure that an attribute is given for all vertices
            if (attrib.size() != _numberOfVertices) {
                throw std::runtime_error("Number of _attributes("+std::to_string(attrib.size())+") does not match the number of vertices("+std::to_string(_numberOfVertices)+")");
            }

            //update offset index
            _attributes.emplace_back(std::pair<int,int>(_currentOffset,2));
            _currentOffset+=2;

            //add the attribute at the end of each vertex
            for (size_t i = 0; i < _vertices.size(); i++) {
                _vertices.at(i).push_back(attrib.at(i).x);
                _vertices.at(i).push_back(attrib.at(i).y);
            }
        }

        void OpenGLMesh::addAttribute(const std::vector<glm::vec3> &attrib)
        {
            //check if this object was finalized
            if (isUploaded()) {
                throw std::runtime_error("Trying to add _attributes to finalized OGLObject");
            }

            //make sure that an attribute is given for all vertices
            if (attrib.size() != _numberOfVertices) {
                throw std::runtime_error("Number of _attributes("+std::to_string(attrib.size())+") does not match the number of vertices("+std::to_string(_numberOfVertices)+")");
            }

            //update offset index
            _attributes.emplace_back(std::pair<int,int>(_currentOffset,3));
            _currentOffset+=3;

            //add the attribute at the end of each vertex
            for (size_t i = 0; i < _vertices.size(); i++) {
                _vertices.at(i).push_back(attrib.at(i).x);
                _vertices.at(i).push_back(attrib.at(i).y);
                _vertices.at(i).push_back(attrib.at(i).z);
            }
        }

        void OpenGLMesh::addAttribute(const std::vector< glm::vec4 > &attrib)
        {
            //check if this object was finalized
            if (isUploaded()) {
                throw std::runtime_error("Trying to add _attributes to finalized OGLObject");
            }

            //make sure that an attribute is given for all vertices
            if (attrib.size() != _numberOfVertices) {
                throw std::runtime_error("Number of _attributes("+std::to_string(attrib.size())+") does not match the number of vertices("+std::to_string(_numberOfVertices)+")");
            }

            //update offset index
            _attributes.emplace_back(std::pair<int,int>(_currentOffset,4));
            _currentOffset+=4;

            //add the attribute at the end of each vertex
            for (size_t i = 0; i < _vertices.size(); i++) {
                _vertices.at(i).push_back(attrib.at(i).x);
                _vertices.at(i).push_back(attrib.at(i).y);
                _vertices.at(i).push_back(attrib.at(i).z);
                _vertices.at(i).push_back(attrib.at(i).w);
            }
        }

        void OpenGLMesh::upload()
        {
            Mesh::upload();

            /// finalize
            GLfloat* vertexData = new GLfloat[_currentOffset*_vertices.size()];
            GLint* indexData = new GLint[_verticesPerFace*_indices.size()];

            for (size_t i = 0; i < _vertices.size(); i++) {
                for (int o = 0; o < _currentOffset; o ++) {
                    vertexData[i*_currentOffset+o] = _vertices.at(i).at(o);
                }
            }

            //create an index array
            for (size_t i =0; i< _indices.size(); i++) {
                for (size_t j= 0; j < _verticesPerFace; j++) {
                    indexData[i*_verticesPerFace+j] = _indices.at(i).at(j);
                }
            }

            //empty unnecessary vectors (we do need the _attributes vector later!)
            _vertices.clear();
            _indices.clear();

            /// upload

            //create a Vertex Array Object
            glGenVertexArrays(1,&_vao);
            glBindVertexArray(_vao);

            //create a Vertex Buffer Object
            glGenBuffers(1,&_vbo);
            glBindBuffer(GL_ARRAY_BUFFER,_vbo);

            // upload data to OpenGL
            glBufferData(GL_ARRAY_BUFFER,_numberOfVertices*_currentOffset*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
            //define and enable the vertex attribute pointers
            for (size_t i = 0; i < _attributes.size(); i++) {
                glVertexAttribPointer(i,_attributes.at(i).second,GL_FLOAT, GL_FALSE,(_attributes.size() == 1)? 0: (_currentOffset/*-_attributes.at(i).second*/)*sizeof(GLfloat),
                                      (GLvoid*) (_attributes.at(i).first*sizeof(GLfloat)));
                glEnableVertexAttribArray(i);
            }


            //create an index buffer
            glGenBuffers(1,&_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

            //upload the index data to OpenGL
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfFaces*_verticesPerFace* sizeof(GLint), indexData, GL_STATIC_DRAW);

            //unbind buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            delete[] vertexData;
            delete[] indexData;
        }

        GLuint OpenGLMesh::getID() {
            return _vao;
        }
    }
}