//
// Created by Paul Bittner on 18.03.2020.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include <paxcore/rendering/config/PointCloudSettings.h>
#include "meshfold/properties/PointCloudSprite.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PointCloudSprite)

    ClassMetadata PointCloudSprite::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(texture)).addFlag(EngineFieldFlags::IsResource | Field::IsMandatory);
        m.add(paxfieldof(pointSize));
        return m;
    }

    void PointCloudSprite::created() {
        init();
    }

    void PointCloudSprite::init() {
        const auto w = float(texture->getWidth());
        const auto h = float(texture->getHeight());

        originalpositions.resize(size_t(w * h));
        uvs.resize(originalpositions.size());
        positions.resize(originalpositions.size());
        pointsizes.resize(originalpositions.size());

        float minX = - w / 2.f;
        float maxX = + w / 2.f;
        float minY = - h / 2.f;
        float maxY = + h / 2.f;

        glm::vec2 halfPixel = 1.f / (2.f*glm::vec2(w,h));

        int i = 0;
        for (float y = 0; y < h; y += 1.f) {
            for (float x = 0; x < w; x += 1.f) {
                originalpositions[i] = {
                        minX + (maxX - minX) * x / w,
                        minY + (maxY - minY) * y / h
                };

                uvs[i] = glm::vec2(x / w, y / h) + halfPixel;
                uvs[i].y = 1 - uvs[i].y;

                pointsizes[i] = 1.f;
                ++i;
            }
        }

        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        std::shared_ptr<Mesh> mesh = meshFactory->create(originalpositions, {});
        mesh->addAttribute(Mesh::UVs, uvs);
        mesh->addAttribute(PointSizes, pointsizes);
        mesh->setFaceMode(Mesh::FaceMode::Points);
        mesh->upload();

        meshNode.setMesh(mesh);
        textureNode.setTexture(texture);
        textureNode.addChild(&meshNode);

        initShader();
    }

    void PointCloudSprite::initShader() {
        Services::Instance().get<PointCloudSettings>()->init(getShader().get());
    }

    PointCloudSprite::PointCloudSprite() : Graphics(), textureNode(nullptr) {}
    PointCloudSprite::PointCloudSprite(const std::shared_ptr<Texture> & texture) : Graphics(), texture(texture), textureNode(texture) {
        init();
    }

    void PointCloudSprite::render(RenderOptions &renderOptions) {
        //float oldPointSize = renderOptions.getPointSize();
        //renderOptions.setPointSize(scale * pointSize);

        Graphics::render(renderOptions);
        textureNode.render(renderOptions);

        //renderOptions.setPointSize(oldPointSize);
    }

    void PointCloudSprite::setShader(const std::shared_ptr<Shader> &shader) {
        Super::setShader(shader);
        initShader();
    }
}