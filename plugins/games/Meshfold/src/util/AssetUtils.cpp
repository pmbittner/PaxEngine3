//
// Created by Paul Bittner on 13.04.2020.
//

#include "meshfold/util/AssetUtils.h"

namespace PAX::AssetUtils {
    Mesh* getFirstMeshYouCanFind(const std::shared_ptr<Asset> & asset) {
        const auto & meshes = asset->getMeshes();
        if (meshes.empty()) {
            for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
                Mesh * m = getFirstMeshYouCanFind(child);
                if (m) return m;
            }
        } else {
            return meshes[0].mesh.get();
        }

        return nullptr;
    }

    std::shared_ptr<Texture> getFirstTextureYouCanFind(const std::shared_ptr<Asset> & asset) {
        for (const Asset::Part & p : asset->getMeshes()) {
            if (p.material->diffuse.texture) {
                return p.material->diffuse.texture;
            }
        }

        for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
            std::shared_ptr<Texture> tex = getFirstTextureYouCanFind(child);
            if (tex) {
                return tex;
            }
        }

        return nullptr;
    }

    void setAllDiffuseTextures(const std::shared_ptr<Asset> & asset, const std::shared_ptr<Texture> & texture) {
        for (const Asset::Part & p : asset->getMeshes()) {
            if (p.material->diffuse.texture) {
                p.material->diffuse.texture = texture;
            }
        }

        for (const std::shared_ptr<Asset> & child : asset->getChildren()) {
            setAllDiffuseTextures(child, texture);
        }
    }
}