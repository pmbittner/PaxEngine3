//
// Created by Bittner on 01/03/2019.
//

#include <paxutil/json/JsonLoader.h>
#include <paxutil/io/FileTypeChecker.h>
#include <paxutil/resources/Resources.h>
#include <fstream>

namespace PAX {
    namespace Json {
        bool JsonLoader::canLoad(PAX::Path path) const {
            Util::FileTypeChecker formats({"JSON"});
            return formats.check(path);
        }

        std::shared_ptr<nlohmann::json> JsonLoader::load(PAX::Path path) {
            try {
                std::ifstream fileStream(path.c_str());
                nlohmann::json j;
                fileStream >> j;
                return std::make_shared<nlohmann::json>(j);
            }
            catch (nlohmann::json::parse_error &e) {
                std::cerr
                        << "[PAX::JsonLoader::load]: File "
                        << path
                        << " could not be parsed:\n"
                        << e.what() << '\n'
                        << "exception id: " << e.id << '\n'
                        << "byte position of error: " << e.byte << std::endl;
                return nullptr;
            }
        }

        std::shared_ptr<nlohmann::json>
        JsonLoader::loadToOrGetFromResources(Resources &resources, const VariableHierarchy &parameters) {
            // Only one entry is required, namely the Path
            if (parameters.values.size() == 1) {
                const std::string &key = parameters.values.begin()->first;
                if (!key.empty()) {
                    return resources.loadOrGet<nlohmann::json>(Path(key));
                }
                const std::string &value = parameters.values.begin()->second;
                if (!value.empty()) {
                    return resources.loadOrGet<nlohmann::json>(Path(value));
                }
            }

            return nullptr;
        }
    }
}