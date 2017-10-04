//
// Created by Paul on 04.10.2017.
//

#include <utility/StringUtils.h>

namespace PAX {
    namespace Util {
        void ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
        }

        void rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        }

        void trim(std::string &s) {
            ltrim(s);
            rtrim(s);
        }

        std::string trimmed(std::string s) {
            trim(s);
            return s;
        }

        std::string getExtension(std::string path) {
            auto dotIndex = path.find_last_of('.');

            if (dotIndex == std::string::npos)
                return "";

            return path.substr(dotIndex + 1);
        }
    }
}