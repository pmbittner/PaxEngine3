//
// Created by Paul Bittner on 18.03.2020.
//

#include <paxutil/reflection/EngineFieldFlags.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>
#include "meshfold/PointCloudSprite.h"

namespace PAX {
    PAX_PROPERTY_IMPL(PointCloudSprite)

    ClassMetadata PointCloudSprite::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(image)).flags = EngineFieldFlags::IsResource;
        return m;
    }

    void PointCloudSprite::created() {
        init();
    }

    void PointCloudSprite::init() {
        pixels.resize(image->getWidth() * image->getHeight());
        directions.resize(pixels.size());

        const float w = float(image->getWidth());
        const float h = float(image->getHeight());

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
                ++i;
            }
        }

        auto * meshFactory = Services::GetFactoryService().get<MeshFactory>();
        // todo:: enable point clouds:
        // Todo: uncomment meshnode render
        //std::shared_ptr<Mesh> mesh = meshFactory->create()
    }

    PointCloudSprite::PointCloudSprite() : Graphics() {}
    PointCloudSprite::PointCloudSprite(const std::shared_ptr<Image> &image) : Graphics(), image(image) {
        init();
    }

    void PointCloudSprite::render(RenderOptions &renderOptions) {
        Graphics::render(renderOptions);
        //meshNode.render(renderOptions);
    }
}