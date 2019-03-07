//
// Created by paul on 02.12.18.
//

#ifndef PAXENGINE3_SETTINGS_H
#define PAXENGINE3_SETTINGS_H

#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#include "../StringUtils.h"

namespace PAX {
    class SettingsFileRow {
    public:
        SettingsFileRow(char separator, bool trimValues);

        std::string const &operator[](std::size_t index) const;
        std::size_t size() const;
        std::istream & readNextRow(std::istream &str);

    private:
        std::vector<std::string> m_data;
        char separator;
        bool trimValues;
    };

    class Settings
    {
    private:
        friend class SettingsFileRow;

        static constexpr char Comment = '#';
        static constexpr const char* IncludeDirective = "include";

        // built-in variables
        struct PreDefinedVariable {
            static constexpr const char* CurrentPath = "CURRENT_PATH";
            static constexpr const char* CurrentDirectory = "CURRENT_DIR";
        };

        std::map<std::string, std::string> settings;
        std::vector<std::string> parsedFiles;

        bool printDebugMessages;

        std::string directoryFromPath(const std::string& path);

    public:
        /**
         * Creates empty settings.
         */
        explicit Settings(bool printDebugMessages = false);

        /**
         * Creates settings from a file by parsing it immediately.
         */
        explicit Settings(const std::string& path, char separator = '=', bool trimValues = true);

        /**
         * Parses a given file and adds its variables to this Settings.
         * Variables, that already exist, may be overwritten, if they occur in the given file, too.
         */
        void parse(const std::string& path, char separator = '=', bool trimValues = true);

        ~Settings() = default;

        /**
         * Adds a setting manually.
         * @param var The variable name to set.
         * @param value The value the variable should have as a string.
         */
        void set(const std::string& varName, const std::string& value);
        bool has(const std::string& varName) const;

    private:
        void check(const std::string& varName) const;

        template<typename T>
        std::vector<T> getTypeVector(const std::string &varName) const {
            std::vector<std::string> stringTuple = getTypeVector<std::string>(varName);
            std::vector<T> tuple(stringTuple.size());

            for (unsigned int i = 0; i < stringTuple.size(); ++i) {
                tuple[i] = Util::String::tryParse<T>(stringTuple[i]);
            }

            return tuple;
        }

    public:
        bool writeToFile(const std::string& path, bool overwrite = false) const;

        /**
         * Returns false if the value is '0' or 'false'. Other values will result
         * in returning true.
         */
        template<typename T = std::string>
        T get(const std::string& varName) const {
            check(varName);
            return Util::String::tryParse<T>(settings.at(varName));
        }

        template<typename T = std::string>
        T getOrDefault(const std::string& varName, const T& defaultValue = T()) const {
            if (has(varName))
                return Util::String::tryParse<T>(settings.at(varName));
            else
                return defaultValue;
        }

        template<typename T = std::string>
        std::vector<T> getVector(const std::string& varName) const {
            return getTypeVector<T>(varName);
        }

        template<typename T = std::string>
        std::vector<T> getVectorOrDefault(const std::string& varName, const std::vector<T>& defaultValue = {}) const {
            if (has(varName))
                return getTypeVector<T>(varName);
            else
                return defaultValue;
        }
    };

    template<> std::vector<std::string> Settings::getTypeVector<std::string>(const std::string &varName) const;
}

#endif //PAXENGINE3_SETTINGS_H
