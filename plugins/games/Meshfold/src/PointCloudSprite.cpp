//
// Created by Paul Bittner on 18.03.2020.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include "meshfold/PointCloudSprite.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PointCloudSprite)

    ClassMetadata PointCloudSprite::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(texture)).flags = EngineFieldFlags::IsResource;
        return m;
    }

    void PointCloudSprite::created() {
        init();
    }

    void PointCloudSprite::init() {
        const float w = float(texture->getWidth());
        const float h = float(texture->getHeight());

        pixels.resize(size_t(w * h));
        uvs.resize(pixels.size());
        directions.resize(pixels.size());


        float minX = - w / 2.f;
        float maxX = + w / 2.f;
        float minY = - h / 2.f;
        float maxY = + h / 2.f;

        int i = 0;
        for (float y = 0; y < h; y += 1.f) {
            for (float x = 0; x < w; x += 1.f) {
                pixels[i] = {
                        minX + (maxX - minX) * x / w,
                        minY + (maxY - minY) * y / h
                };
                uvs[i] = {x / w, 1 - y / h};
                ++i;
            }
        }

        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        std::shared_ptr<Mesh> mesh = meshFactory->create(pixels, {});
        mesh->addAttribute(Mesh::UVs, uvs);
        mesh->setFaceMode(Mesh::FaceMode::Points);
        mesh->upload();

        meshNode.setMesh(mesh);
        textureNode.setTexture(texture);
        textureNode.addChild(&meshNode);
    }

    PointCloudSprite::PointCloudSprite() : Graphics(), textureNode(nullptr) {}
    PointCloudSprite::PointCloudSprite(const std::shared_ptr<Texture> & texture) : Graphics(), texture(texture), textureNode(texture) {
        init();
    }

    void PointCloudSprite::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);
        textureNode.render(renderOptions);
    }
}