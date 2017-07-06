//
// Created by Paul on 06.07.2017.
//

#ifndef PAXENGINE3_STRINGUTILS_H
#define PAXENGINE3_STRINGUTILS_H

#include <string>
#include <algorithm>

#define PAX_UTIL_STRING_EQUALS !strcmp
#define PAX_UTIL_STRING_NEQUALS strcmp

namespace PAX {
    namespace Util {

        // trim from start (in place)
        inline void ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
        }

        // trim from end (in place)
        inline void rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        }

        // trim from both ends (in place)
        inline void trim(std::string &s) {
            ltrim(s);
            rtrim(s);
        }

        // trim from both ends (copying)
        inline std::string trimmed(std::string s) {
            trim(s);
            return s;
        }
    }
}
#endif //PAXENGINE3_STRINGUTILS_H
