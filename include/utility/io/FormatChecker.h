//
// Created by Paul on 04.11.2017.
//

#ifndef PAXENGINE3_FORMATCHECKER_H
#define PAXENGINE3_FORMATCHECKER_H

#include <string>
#include <algorithm>
#include <utility/stdutils/CollectionUtils.h>

namespace PAX {
    namespace Util {
        class FormatChecker {
            std::vector<std::string> _formats;

        public:
            FormatChecker(std::vector<const char*> formats) {
                for (std::string format : formats) {
                    std::transform(format.begin(), format.end(), format.begin(), ::tolower);
                    _formats.push_back(format);
                }
            }

            bool check(std::string extension) {
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                return Util::vectorContains(_formats, extension);
            }

            bool check(const char* extension) {
                check(std::string(extension));
            }
        };
    }
}

#endif //PAXENGINE3_FORMATCHECKER_H
