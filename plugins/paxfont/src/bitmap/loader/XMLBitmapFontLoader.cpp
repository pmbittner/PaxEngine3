//
// Created by Paul Bittner on 14.03.2021.
//

#include <paxutil/io/FileTypeChecker.h>
#include "paxfont/bitmap/loader/XMLBitmapFontLoader.h"

#include <fstream>
#include <paxcore/service/Services.h>

namespace PAX::Font {
    bool XMLBitmapFontLoader::canLoad(Path p) const {
        static Util::FileTypeChecker c({"xml"});
        return c.check(p);
    }

    std::shared_ptr<BitmapFont> XMLBitmapFontLoader::load(Path p) {
        // load bitmap
        Path texturePath = p.withoutFileEnding().toString() + ".png";
        std::shared_ptr<Texture> bitmap = Services::GetResources().loadOrGet<Texture>(texturePath);

        // Open file
        std::ifstream file(p.toString());
        if (!file.is_open()) {
            PAX_THROW_RUNTIME_ERROR("Could not read file " << p.toAbsolute() << "!");
        }

        FontMetadata metadata;
        std::vector<CharacterInfo> charset;

        std::string line;
        while (std::getline(file, line)) {
            String::trim(line);
            if (String::startsWith(line, "<?xml") || String::startsWith(line, "</Font>")) {
                // we have the header -> skip
                continue;
            }
            // drop beginning "<"
            line = line.substr(1);
            String::trim(line);

            // 5 = length of "Font " and "Char "... nice coincidence
            const bool parseMetadata = String::startsWith(line, "Font");
            line = line.substr(5, line.size() - 5);
            CharacterInfo c;
            while (!line.empty()) {
                if (line == "/>" || line == ">") {
                    // we are done
                    break;
                }

                const size_t nextEqualsSign = line.find_first_of('=');
                const std::string key = line.substr(0, nextEqualsSign);
                line = line.substr(line.find_first_of('"') + 1);

                const size_t posOfEndQuotes = line.find_first_of('"');
                const std::string val = line.substr(0, posOfEndQuotes);
                line = line.substr(posOfEndQuotes + 1);
                String::trim(line);

                if (parseMetadata) {
                    if (key == "size") {
                        metadata.size = String::convertTo<int>(val);
                    } else if (key == "family") {
                        metadata.family = val;
                    } else if (key == "height") {
                        metadata.height = String::convertTo<int>(val);
                    } else if (key == "style") {
                        metadata.style = val;
                    }
                } else {
                    if (key == "width") {
                        c.width = String::convertTo<int>(val);
                    } else if (key == "offset") {
                        c.textLineOffset = String::convertTo<glm::ivec2>(val);
                    } else if (key == "rect") {
                        const auto rect = String::convertTo<glm::ivec4>(val);
                        c.pos  = glm::ivec2(rect.x, rect.y);
                        c.size = glm::ivec2(rect.z, rect.w);
                    } else if (key == "code") {
                        c.key = val;
                    }
                }
            }
            if (!parseMetadata) {
                charset.push_back(c);
            }
        }

        return std::make_shared<BitmapFont>(metadata, bitmap, charset);
    }
}