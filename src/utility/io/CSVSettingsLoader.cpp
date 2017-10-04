//
// Created by Paul on 06.07.2017.
//

#include <cstring>
#include <utility/io/CSVRow.h>
#include <utility/io/CSVSettingsLoader.h>
#include <utility/StringUtils.h>

namespace PAX {
    namespace Util {
        CSVSettingsLoader::CSVSettingsLoader(std::string path, char separator, bool trimValues) {
            std::ifstream file(path);
            CSVRow row(separator);
            while (file >> row)
            {
                if (!row[0].empty() && row[0].front() != ICG_CSVSETTINGS_COMMENT) {
                    std::string row0(trimValues ? trimmed(row[0]) : row[0]);
                    std::string row1(trimValues ? trimmed(row[1]) : row[1]);
                    settings[row0] = row1;
                }
            }
        }

        bool CSVSettingsLoader::getBool(std::string key) {
            std::string value = settings[key];
            return PAX_UTIL_STRING_NEQUALS(value.c_str(), "0") && PAX_UTIL_STRING_NEQUALS(value.c_str(), "false");
        }

        float CSVSettingsLoader::getFloat(std::string key) {
            return (float)getDouble(key);
        }

        double CSVSettingsLoader::getDouble(std::string key) {
            return std::stod(settings[key]);
        }

        int CSVSettingsLoader::getInt(std::string key) {
            return std::atoi(settings[key].c_str());
        }

        std::string const& CSVSettingsLoader::operator[](std::string key) {
            return settings[key];
        }
    }
}