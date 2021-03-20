//
// Created by Paul on 09.01.2018.
//

#include <paxutil/lib/GlmIncludes.h>

#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxcore/service/Services.h>
#include <paxcore/gameentity/property/Size.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include <paxcore/rendering/primitives/PrimitiveFactory.h>

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
            QuadMesh = PrimitiveFactory::CreateQuad();
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
                glm::scale(glm::mat4(1.f), event.size->getSizeUnscaled())
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

    void SpriteGraphics::setMesh(const std::shared_ptr<Mesh> &mesh) {
        _meshNode.setMesh(mesh);
    }

    void SpriteGraphics::setTexture(const std::shared_ptr<Texture> &texture) {
        _textureNode.setTexture(texture);
    }

    const std::shared_ptr<Texture>& SpriteGraphics::getTexture() const {
        return _textureNode.getTexture();
    }

    const std::shared_ptr<Mesh> & SpriteGraphics::getMesh() const {
        return _meshNode.getMesh();
    }

    void SpriteGraphics::render(PAX::RenderOptions &renderOptions) {
        if (Shader * shader = renderOptions.getShaderOptions().getShader()) {
            shader->setUniform("spriteResolution", _texture->getSize());
        }

        Super::render(renderOptions);
    }
}