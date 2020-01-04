//
// Created by Paul on 04.11.2017.
//

#ifndef POLYPROPYLENE_FORMATCHECKER_H
#define POLYPROPYLENE_FORMATCHECKER_H

#include <string>
#include <algorithm>
#include <polypropylene/stdutils/CollectionUtils.h>
#include <iostream>
#include <polypropylene/stdutils/StringUtils.h>

namespace PAX::Util {
    class FileTypeChecker {
        std::vector<std::string> _formats;

    public:
        explicit FileTypeChecker(const std::vector<const char*> & formats) {
            for (std::string format : formats) {
                if (!String::startsWith(format, ".")) {
                    format.insert(0, 1, '.');
                }
                std::transform(format.begin(), format.end(), format.begin(), ::tolower);
                _formats.push_back(format);
            }
        }

        PAX_NODISCARD bool check(const std::string& path) const {
            std::string p = path;
            std::transform(p.begin(), p.end(), p.begin(), ::tolower);

            for (const std::string & format : _formats) {
                if (String::endsWith(p, format))
                    return true;
            }

            return false;
        }
    };
}

#endif //POLYPROPYLENE_FORMATCHECKER_H
