//
// Created by Paul on 06.07.2017.
//
#ifndef PAXENGINE3_CSVSETTINGSLOADER_H
#define PAXENGINE3_CSVSETTINGSLOADER_H

#include <map>
#include "CSVRow.h"

#define ICG_CSVSETTINGS_COMMENT '#'

namespace PAX {
    namespace Util {
        class CSVSettingsLoader
        {
        private:
            std::map<std::string, std::string> settings;

        public:
            CSVSettingsLoader(std::string path, char separator = ',', bool trimValues = false);

            /**
             * Returns false if the value is '0' or 'false'. Other values will result
             * in returning true.
             */
            bool getBool(std::string key);
            float getFloat(std::string key);
            double getDouble(std::string key);
            int getInt(std::string key);
            std::string const &operator[](std::string key);
        };
    }
}

#endif //PAXENGINE3_CSVSETTINGSLOADER_H
