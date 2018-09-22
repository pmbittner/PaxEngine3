//
// Created by Paul on 09.01.2018.
//

#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/io/resources/Resources.h>
#include <paxcore/service/Services.h>
#include <paxcore/entity/component/Size.h>

namespace PAX {
    std::shared_ptr<Mesh> SpriteGraphics::QuadMesh = nullptr;

    std::shared_ptr<Mesh> SpriteGraphics::GetMesh() {
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

            std::cout << "[SpriteGraphics::GetMesh] create QuadMesh" << std::endl;
            QuadMesh = Services::GetFactory().create<Mesh>(&vertices, &indices);
            QuadMesh->addAttribute(Mesh::UVs, texCoords);
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
    }

    glm::vec2 SpriteGraphics::getSpriteSize() const {
        return glm::vec2(_texture->getWidth(), _texture->getHeight());
    }

    void SpriteGraphics::onSizeChanged(SizeChangedEvent &event) {
        _trafoNode.setTransformation(
                glm::scale(glm::mat4(1), event.size->getSizeUnscaled())
        );
    }

    void SpriteGraphics::setShader(std::shared_ptr<Shader> &shader) {
        _meshNode.cacheUniformsFor(shader);
        Graphics::setShader(shader);
    }

    void SpriteGraphics::attached(Entity &entity) {
        SceneGraphGraphics::attached(entity);

        entity.getEventService().add<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);

        glm::vec3 spriteSize = glm::vec3(getSpriteSize(), 0);
        std::shared_ptr<Size> size = entity.get<Size>();
        if (size) {
            size->setSize(spriteSize);
        } else {
            size = Services::GetEntityComponentAllocationService().create<Size>(spriteSize);
            entity.add(size);
        }
    }

    void SpriteGraphics::detached(Entity &entity) {
        SceneGraphGraphics::detached(entity);
        entity.getEventService().remove<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);
    }
}