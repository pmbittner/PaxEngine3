//
// Created by Paul on 04.09.2018.
//

#ifndef PAXENGINE3_ASSET_H
#define PAXENGINE3_ASSET_H

#include <memory>

#include "../interface/Renderable.h"
#include "Mesh.h"
#include "Material.h"
#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>

namespace PAX {
    class Asset : public Renderable {
    public:
        // I know this name is stupid, but I didn't come up with a better one.
        struct Part {
            const std::shared_ptr<Mesh> mesh;
            const std::shared_ptr<Material> material;

            /// \param mesh Can't be null!
            /// \param material Can't be null!
            Part(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<Material> & material);
            Part(const Part & other);
        };

    private:
        std::vector<std::shared_ptr<Asset>> children;
        glm::mat4 transformation;
        std::vector<Part> meshes;

    public:
        /// Creates a new Asset with the given mesh and material. Optional a relative transformation can be applied to the mesh.
        /// \param meshes may be empty
        /// \param transformation relative transformation to parent assets (default is identity)
        explicit Asset(const std::vector<Part>& meshes, const glm::mat4 & transformation = glm::mat4(1.0f));
        ~Asset() override;

        /*
        /// Adds a given asset to the children of this asset.
        /// \param asset The argument is moved and will be owned by the called Asset afterwards.
         */
        void addChild(const std::shared_ptr<Asset> & asset);

        void render(RenderOptions &renderOptions) override;

        virtual void print(const std::string& indent = "") const;

        void upload();

        PAX_NODISCARD const std::vector<std::shared_ptr<Asset>> &getChildren() const;
        PAX_NODISCARD const glm::mat4 &getTransformation() const;
        PAX_NODISCARD const std::vector<Part> &getMeshes() const;
    };
}

#endif //PAXENGINE3_ASSET_H
