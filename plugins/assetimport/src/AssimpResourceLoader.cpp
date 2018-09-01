//
// Created by Paul on 30.08.2018.
//

#include <AssimpResourceLoader.h>
#include <utility/io/FileTypeChecker.h>
#include <core/service/Services.h>

#include <vector>

/// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PAX {
    namespace AssetImport {
        bool AssimpResourceLoader::canLoad(Path p) {
            static Util::FileTypeChecker formatChecker({
                "3ds"
            });
            return formatChecker.check(p);
        }

        std::shared_ptr<Mesh> AssimpResourceLoader::load(Path p) {
            Assimp::Importer importer;

            // TODO: Find optimal default value and make this configurable
            unsigned int postProcessingFlags = aiProcessPreset_TargetRealtime_Fast;
            const aiScene* scene = importer.ReadFile(p.toString(), postProcessingFlags);

            if (!scene) {
                // Import failed
                std::stringstream errorStream;
                errorStream << "[PAX::AssetImport::AssimpResourceLoader::load] " << importer.GetErrorString();
                throw std::runtime_error(errorStream.str());
            }

            // Now traverse the imported scene

            // sample test code
            std::vector<glm::vec3> vertices({
                                           {0, 0, 0},
                                           {0, 1, 0},
                                           {1, 1, 0}
                                   });
            std::vector<glm::ivec3> faces({
                                            {0, 1, 2}
                                    });

            std::shared_ptr<Mesh> m = Services::GetFactory().create<Mesh>(&vertices, &faces);
            return m;
        }
    }
}