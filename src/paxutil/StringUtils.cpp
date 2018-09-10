//
// Created by Paul on 04.10.2017.
//

#include <paxutil/StringUtils.h>

namespace PAX {
    namespace Util {
        void ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
        }

        void rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            }).base(), s.end());
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

        void str_replace(std::string& string, const char& from, const char& to) {
            std::replace(string.begin(), string.end(), from, to);
        }
    }
}