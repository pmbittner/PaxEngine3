//
// Created by Paul on 04.09.2018.
//

#ifndef PAXENGINE3_ASSET_H
#define PAXENGINE3_ASSET_H

#include <memory>

#include "../interface/Renderable.h"
#include "../interface/Shaded.h"
#include "Mesh.h"
#include "Material.h"
#include <paxcore/rendering/scenegraph/nodes/TransformationNode.h>

namespace PAX {
    class Asset : public Renderable, public Shaded {
    public:
        // I know this name is stupid, but I didn't come up with a better one.
        struct Part {
            const std::shared_ptr<Mesh> _mesh;
            const std::shared_ptr<Material> _material;

            /// \param mesh Can't be null!
            /// \param material Can't be null!
            Part(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<Material> & material);
            Part(const Part & other);
        };

    private:
        std::vector<std::shared_ptr<Asset>> _children;
        glm::mat4 _transformation;
        std::vector<Part> _meshes;

    public:
        /// Creates a new Asset with the given mesh and material. Optional a relative transformation can be applied to the mesh.
        /// \param meshes may be empty
        /// \param transformation relative transformation to parent assets (default is identity)
        Asset(const std::vector<Part>& meshes, const glm::mat4 & transformation = glm::mat4());
        virtual ~Asset();

        /*
        /// Adds a given asset to the children of this asset.
        /// \param asset The argument is moved and will be owned by the called Asset afterwards.
         */
        void addChild(const std::shared_ptr<Asset> & asset);

        virtual void render(RenderOptions &renderOptions) override;
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader) override;

        virtual void print(const std::string& indent = "") const;
    };
}

#endif //PAXENGINE3_ASSET_H
