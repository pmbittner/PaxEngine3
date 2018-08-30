//
// Created by Paul on 30.08.2018.
//

#include <AssimpResourceLoader.h>
#include <utility/io/FileTypeChecker.h>
#include <core/service/Services.h>

#include <vector>

namespace PAX {
    namespace AssetImport {
        bool AssimpResourceLoader::canLoad(PAX::Path p) {
            static Util::FileTypeChecker formatChecker({
                "3ds"
            });
            return formatChecker.check(p);
        }

        std::shared_ptr<Mesh> AssimpResourceLoader::load(PAX::Path p) {
            return Services::GetResources().load<Mesh>(
                    std::vector<glm::vec3>({
                        {0, 0, 0},
                        {0, 1, 0},
                        {1, 1, 0}
                    }),
                    std::vector<glm::ivec3>({
                        {0, 1, 2}
                    })
            );
        }
    }
}