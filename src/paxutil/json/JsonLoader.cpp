//
// Created by Bittner on 01/03/2019.
//

#include <paxutil/json/JsonLoader.h>
#include <paxutil/io/FileTypeChecker.h>
#include <fstream>

namespace PAX {
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
        catch (nlohmann::json::parse_error& e) {
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
}