//
// Created by paul on 02.12.18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

#include <paxutil/log/Errors.h>
#include <paxutil/io/Settings.h>
#include <paxutil/stdutils/CollectionUtils.h>
#include <paxutil/StringVariables.h>

namespace PAX {
    SettingsFileRow::SettingsFileRow(char separator,  bool trimValues) : separator(separator), trimValues(trimValues) {}

    std::string const &SettingsFileRow::operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t SettingsFileRow::size() const {
        return m_data.size();
    }

    std::istream & SettingsFileRow::readNextRow(std::istream &str) {
        m_data.clear();

        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        bool comment = false;

        while (!comment && std::getline(lineStream, cell, separator)) {
            size_t commentPos = cell.find(Settings::Comment);
            if (commentPos != std::string::npos) {
                // We found an inline comment
                // Ignore the rest of the line
                cell = cell.substr(0, commentPos);
                comment = true;
            }

            if (trimValues)
                cell = String::trimmed(cell);

            m_data.push_back(cell);
        }

        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty()) {
            // If there was a trailing comma then add an empty element.
            m_data.emplace_back("");
        }

        return str;
    }



    Settings::Settings() = default;

    Settings::Settings(const Path & path, char separator, bool trimValues) : Settings() {
        parse(path, separator, trimValues);
    }

    void Settings::parse(const Path& path, char separator, bool trimValues) {
        // Check if file is already parsed
        if (Util::vectorContains<std::string>(parsedFiles, path)) {
            PAX_LOG(PAX::Log::Level::Warn, "The file " << path << " was already parsed! Maybe there is a cyclic or duplicate include?");
            return;
        }

        // Pre defined variables
        Path currentDirectory = path.getDirectory();

        // Open file
        std::ifstream file(path.toString());
        if (!file.is_open()) {
            PAX_THROW_RUNTIME_ERROR("The file " << path << " was already parsed! Maybe there is a cyclic or duplicate include?");
        }

        SettingsFileRow row(separator, trimValues);

        PAX_LOG_DEBUG(PAX::Log::Level::Info, "Start parsing " << path);

        int lineNumber = 1;
        while (row.readNextRow(file))
        {
            if (!row[0].empty()) {
                if (row[0] == IncludeDirective) {
                    std::string newPath = path.getDirectory() + row[1];
                    PAX_LOG_DEBUG(PAX::Log::Level::Info, "Include file " << newPath);
                    parse(newPath, separator, trimValues);
                } else {
                    // check for variables in rhs
                    std::map<std::string, std::string> resolvableVariables(settings);

                    // Predefined variables should be overridable in settings.
                    // Therefore put them into the map only, when they were not set manually already.
                    if (resolvableVariables.find(PreDefinedVariable::CurrentPath) == resolvableVariables.end())
                        resolvableVariables[PreDefinedVariable::CurrentPath] = path.toAbsolute().toString();
                    if (resolvableVariables.find(PreDefinedVariable::CurrentDirectory) == resolvableVariables.end())
                        resolvableVariables[PreDefinedVariable::CurrentDirectory] = currentDirectory.toAbsolute().toString();

                    settings[row[0]] = VariableResolver::resolveVariables(row[1], resolvableVariables);

                    PAX_LOG_DEBUG(PAX::Log::Level::Info, "Parsed setting " << row[0] << " " << separator << " " << settings[row[0]]);
                }
            }

            ++lineNumber;
        }

        parsedFiles.push_back(path);
        PAX_LOG_DEBUG(PAX::Log::Level::Info, "End parsing " << path);
    }

    bool Settings::writeToFile(const Path & path, bool overwrite) const {
        // Do not use std::endl to avoid flushes
        const char lineEnd = '\n';

        bool fileAreadyExists;
        {
            std::ifstream file(path.toString());
            fileAreadyExists = file.good();
        }

        if (!fileAreadyExists || overwrite) {
            std::ofstream file(path.toString());

            if (file) {
                for (auto &kv : settings) {
                    file << kv.first << " = " << kv.second << lineEnd;
                }

                file.close();
                return true;
            } else {
                PAX_LOG(PAX::Log::Level::Warn, "Could not open " << path << "!");
            }
        } else {
            PAX_LOG(PAX::Log::Level::Warn, "File " << path << " already exists!");
        }

        return false;
    }

    void Settings::set(const std::string& varName, const std::string& value) {
        settings[varName] = value;
    }

    bool Settings::has(const std::string& varName) const {
        return settings.find(varName) != settings.end();
    }

    void Settings::check(const std::string& varName) const {
        if (!has(varName)) {
            PAX_THROW_RUNTIME_ERROR("The variable " + varName + " has no entry!");
        }
    }

    template<>
    std::vector<std::string> Settings::getTypeVector<std::string>(const std::string &varName) const {
        auto value = get<std::string>(varName);
        std::vector<std::string> tuple;

        if (String::startsWith(value, "(") && String::endsWith(value, ")")) {
            value = value.substr(1, value.size() - 2);

            size_t pos = 0;
            size_t nextComma;

            do {
                nextComma = value.find(',', pos);
                std::string valueComponent = String::trimmed(value.substr(pos, nextComma - pos));
                tuple.push_back(valueComponent);

                pos = nextComma + 1;
            } while(nextComma != std::string::npos);
        } else {
            PAX_THROW_RUNTIME_ERROR("The variable " + varName + " is not a tuple!");
        }

        return tuple;
    }
}

#undef PAX_SETTINGS_PRINT