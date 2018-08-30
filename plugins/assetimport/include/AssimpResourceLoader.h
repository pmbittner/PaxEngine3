//
// Created by Paul on 30.08.2018.
//

#ifndef PAXENGINE3_ASSIMPRESOURCELOADER_H
#define PAXENGINE3_ASSIMPRESOURCELOADER_H

#include <core/rendering/data/Mesh.h>
#include <core/io/resources/ResourceLoader.h>

namespace PAX {
    namespace AssetImport {
        class AssimpResourceLoader : public ResourceLoader<Mesh, Path> {
        public:
            AssimpResourceLoader() = default;

            virtual bool canLoad(Path p) override;
            virtual std::shared_ptr<Mesh> load(Path p) override;
        };
    }
}
#endif //PAXENGINE3_ASSIMPRESOURCELOADER_H
