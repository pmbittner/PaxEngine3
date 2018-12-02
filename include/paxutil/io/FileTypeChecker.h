//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_FORMATCHECKER_H
#define PAXENGINE3_FORMATCHECKER_H

#include <string>
#include <algorithm>
#include <paxutil/stdutils/CollectionUtils.h>
#include <iostream>
#include <paxutil/StringUtils.h>

namespace PAX {
    namespace Util {
        class FileTypeChecker {
            std::vector<std::string> _formats;

        public:
            FileTypeChecker(const std::vector<const char*> & formats) {
                for (std::string format : formats) {
                    std::transform(format.begin(), format.end(), format.begin(), ::tolower);
                    _formats.push_back(format);
                }
            }

            bool check(const std::string& path) {
                std::string extension = Util::String::getExtension(path);
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                return Util::vectorContains(_formats, extension);
            }
        };
    }
}

#endif //PAXENGINE3_FORMATCHECKER_H
