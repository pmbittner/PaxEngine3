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
            /*implicit*/ FileTypeChecker(const std::vector<const char*> & formats) {
                for (std::string format : formats) {
                    std::transform(format.begin(), format.end(), format.begin(), ::tolower);
                    _formats.push_back(format);
                }
            }

            bool check(const std::string& path) {
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
}

#endif //PAXENGINE3_FORMATCHECKER_H
