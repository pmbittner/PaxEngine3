//
// Created by Paul on 09.01.2018.
//

#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/service/Services.h>
#include <paxcore/gameentity/property/Size.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include <paxutil/resources/Resources.h>
#include <paxutil/reflection/EngineFieldFlags.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::SpriteGraphics)

    void SpriteGraphics::init() {
        if (_texture)
            _texture->setWrapMode(Texture::WrapMode::ClampToEdge, Texture::WrapMode::ClampToEdge);
        _textureNode.setTexture(_texture);

        _meshNode.setMesh(GetMesh());

        SceneGraphGraphics::_scenegraph <<= _trafoNode <<= _textureNode <<= _meshNode;
    }

    SpriteGraphics::SpriteGraphics() : _textureNode(_texture) {}

    void SpriteGraphics::created() {
        Super::created();
        init();
    }

    ClassMetadata SpriteGraphics::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add({"Sprite", paxtypeof(_texture), &_texture, Field::IsMandatory | EngineFieldFlags::IsResource});
        return m;
    }

    std::shared_ptr<Mesh> SpriteGraphics::QuadMesh = nullptr;

    std::shared_ptr<Mesh> SpriteGraphics::GetMesh() {
        if (!QuadMesh) {
            auto* meshFactory = Services::GetFactoryService().get<MeshFactory>();

            if (meshFactory) {
                std::vector<glm::vec3> vertices = {
                        {-0.5f, 0.5f,  0},  // V0
                        {-0.5f, -0.5f, 0},  // V1
                        {0.5f,  -0.5f, 0},  // V2
                        {0.5f,  0.5f,  0}   // V3
                };

                std::vector<glm::ivec3> indices = {
                        {0, 1, 3},  // Top    left  triangle (V0,V1,V3)
                        {3, 1, 2}   // Bottom right triangle (V3,V1,V2)
                };

                std::vector<glm::vec2> texCoords = {
                        {0, 0},
                        {0, 1},
                        {1, 1},
                        {1, 0}
                };

                PAX_LOG(Log::Level::Info, "create QuadMesh");

                QuadMesh = meshFactory->create(vertices, indices);
                QuadMesh->addAttribute(Mesh::UVs, texCoords);
                QuadMesh->upload();
            } else {
                PAX_THROW_RUNTIME_ERROR("Could not create sprite mesh because no MeshFactory is registered at the FactoryService!");
            }
        }

        return QuadMesh;
    }

    SpriteGraphics::SpriteGraphics(const std::shared_ptr<Texture> & texture) : SceneGraphGraphics(),
                                                                              _texture(texture),
                                                                              _trafoNode(),
                                                                              _textureNode(texture),
                                                                              _meshNode(GetMesh())
    {
        init();
    }

    glm::vec2 SpriteGraphics::getSpriteSize() const {
        return glm::vec2(_texture->getWidth(), _texture->getHeight());
    }

    void SpriteGraphics::onSizeChanged(SizeChangedEvent &event) {
        _trafoNode.setTransformation(
                glm::scale(glm::mat4(1), event.size->getSizeUnscaled())
        );
    }

    void SpriteGraphics::attached(GameEntity &entity) {
        SceneGraphGraphics::attached(entity);

        entity.getEventService().add<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);

        glm::vec3 spriteSize = glm::vec3(getSpriteSize(), 0);
        Size* size = entity.get<Size>();
        if (size) {
            size->setSize(spriteSize);
        } else {
            size = new Size(spriteSize);
            entity.add(size);
        }
    }

    void SpriteGraphics::detached(GameEntity &entity) {
        SceneGraphGraphics::detached(entity);
        entity.getEventService().remove<SizeChangedEvent, SpriteGraphics, &SpriteGraphics::onSizeChanged>(this);
    }

    void SpriteGraphics::setTexture(const std::shared_ptr<Texture> &texture) {
        _textureNode.setTexture(texture);
    }

    const std::shared_ptr<Texture>& SpriteGraphics::getTexture() {
        return _textureNode.getTexture();
    }

    void SpriteGraphics::render(PAX::RenderOptions &renderOptions) {
        if (Shader * shader = renderOptions.getShaderOptions().getShader()) {
            shader->setUniform("spriteResolution", _texture->getSize());
        }

        Super::render(renderOptions);
    }
}