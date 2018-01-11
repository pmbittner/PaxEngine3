//
// Created by Paul on 09.01.2018.
//

#include <core/rendering/graphics/SpriteGraphics.h>
#include <glm/gtc/matrix_transform.hpp>
#include <core/io/resources/Resources.h>
#include <core/service/Services.h>

namespace PAX {
    Mesh *SpriteGraphics::QuadMesh = nullptr;

    Mesh* SpriteGraphics::GetMesh() {
        if (!QuadMesh) {
            std::vector<glm::vec3> vertices = {
                    {-0.5f,  0.5f, 0},  // V0
                    {-0.5f, -0.5f, 0},  // V1
                    { 0.5f, -0.5f, 0},  // V2
                    { 0.5f,  0.5f, 0}   // V3
            };

            std::vector<std::vector<int>> indices = {
                    {0, 1, 3},  // Top    left  triangle (V0,V1,V3)
                    {3, 1, 2}   // Bottom right triangle (V3,V1,V2)
            };

            std::vector<glm::vec2> texCoords = {
                    {0, 0},
                    {0, 1},
                    {1, 1},
                    {1, 0}
            };

            QuadMesh = Services::GetRenderFactory()->createMesh(vertices, indices);
            QuadMesh->addAttribute(texCoords);
            QuadMesh->finalize();
            QuadMesh->upload();
        }

        return QuadMesh;
    }

    SpriteGraphics::SpriteGraphics(const std::shared_ptr<Texture> &texture) : SceneGraphGraphics(),
                                                                              _texture(texture),
                                                                        _trafoNode(),
                                                                        _textureNode(texture),
                                                                        _meshNode(GetMesh())
    {
        _scenegraph <<= _trafoNode <<= _textureNode <<= &_meshNode;
        initializeTransformation();
    }

    void SpriteGraphics::initializeTransformation() {
        _trafoNode.setTransformation(glm::scale(glm::mat4(1), glm::vec3(_texture->getWidth(), _texture->getHeight(), 1)));
    }

    void SpriteGraphics::setSpriteScale(const glm::vec2& scale) {
        initializeTransformation();
        _trafoNode.setTransformation(
                glm::scale(_trafoNode.getTransformation(), glm::vec3(scale, 1))
        );
    }

    void SpriteGraphics::registerFlags(Shader::Flags &flags) {
        _meshNode.registerFlags(flags);
    }

    void SpriteGraphics::setShader(std::shared_ptr<Shader> &shader) {
        _meshNode.cacheUniformsFor(shader);
        Graphics::setShader(shader);
    }
}