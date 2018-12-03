//
// Created by paul on 02.12.18.
//

#include <iostream>
#include <regex>
#include <paxutil/io/Settings.h>
#include <paxutil/stdutils/CollectionUtils.h>

#define PAX_SETTINGS_PRINT(body) if (printDebugMessages) { body }

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
                cell = Util::String::trimmed(cell);

            m_data.push_back(cell);
        }

        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty()) {
            // If there was a trailing comma then add an empty element.
            m_data.emplace_back("");
        }

        return str;
    }



    Settings::Settings(bool printDebugMessages) : printDebugMessages(printDebugMessages) {

    };

    Settings::Settings(const std::string& path, char separator, bool trimValues) : Settings() {
        parse(path, separator, trimValues);
    }

    std::string Settings::directoryFromPath(const std::string& path) {
        size_t lastSlashOnWindows      = path.find_last_of('\\');
        size_t lastSlashEverywhereElse = path.find_last_of('/');
        size_t lastSlash = std::string::npos;

        if (lastSlashOnWindows != std::string::npos) {
            if (lastSlashEverywhereElse != std::string::npos) {
                lastSlash = (std::max)(lastSlashOnWindows, lastSlashEverywhereElse);
            } else {
                lastSlash = lastSlashOnWindows;
            }
        } else if (lastSlashEverywhereElse != std::string::npos) {
            lastSlash = lastSlashEverywhereElse;
        }

        if (lastSlash != std::string::npos)
            return path.substr(0, lastSlash);
        else
            return ".";
    }

    void Settings::parse(const std::string& path, char separator, bool trimValues) {
        // Check if file is already parsed
        if (Util::vectorContains<std::string>(parsedFiles, path)) {
            std::cerr << "[Settings] Warning: The file " << path << " was already parsed! Maybe there is a cyclic or duplicate include?" << std::endl;
            return;
        } else {
            parsedFiles.push_back(path);
        }

        // Pre defined variables
        std::string currentDirectory = directoryFromPath(path);

        // Open file
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "[Settings] Unable to open " << path << std::endl;
            throw std::runtime_error("Settings include path not found");
        }

        SettingsFileRow row(separator, trimValues);

        PAX_SETTINGS_PRINT(std::cout << "[Settings] Start parsing " << path << std::endl;)
        int lineNumber = 1;
        while (row.readNextRow(file))
        {
            if (!row[0].empty()) {
                if (row[0] == IncludeDirective) {
                    std::string newPath = directoryFromPath(path) + "/" + row[1];
                    PAX_SETTINGS_PRINT(std::cout << "[Settings]     Include file " << newPath << std::endl;)
                    parse(newPath, separator, trimValues);
                } else {
                    std::string rhs = row[1];

                    // check for variables in rhs
                    {
                        // rhs[varIndex] == VariableDeclaration
                        std::size_t varDecIndex = rhs.find(VariableDeclarationBegin);
                        while (varDecIndex != std::string::npos) {
                            // finds first occurence and hence the end of our var
                            std::size_t varDecEndIndex = rhs.find(VariableDeclarationEnd);

                            if (varDecEndIndex == std::string::npos) {
                                PAX_SETTINGS_PRINT(std::cout << "[Settings]     Warning: Variable declaration end missing (line "
                                          << lineNumber << "): " << row[1] << std::endl;)
                                // terminate since we are left in an infinite loop otherwise
                                break;
                            } else {
                                std::size_t varNameIndex = varDecIndex + strlen(VariableDeclarationBegin);
                                std::size_t varNamelength =
                                        varDecEndIndex - strlen(VariableDeclarationEnd) - varNameIndex + 1;
                                std::string varName = rhs.substr(varNameIndex, varNamelength);
                                std::string varValue;

                                if (!has(varName)) {
                                    // check pre-defined variables
                                    if (varName == PreDefinedVariable::CurrentPath) {
                                        varValue = path;
                                    } else if (varName == PreDefinedVariable::CurrentDirectory) {
                                        varValue = currentDirectory;
                                    } else {
                                        PAX_SETTINGS_PRINT(std::cout << "[Settings]     Warning: Variable not found (line " << lineNumber
                                                  << "): " << varName << std::endl;)
                                    }
                                } else {
                                    varValue = settings[varName];
                                }

                                rhs = rhs.replace(
                                        varDecIndex,
                                        varNamelength + strlen(VariableDeclarationBegin) + strlen(VariableDeclarationEnd),
                                        varValue
                                );
                            }

                            // search for next occurrence
                            varDecIndex = rhs.find(VariableDeclarationBegin);
                        }
                    }

                    settings[row[0]] = rhs;
                    PAX_SETTINGS_PRINT(std::cout << "[Settings]     Parsed setting " << row[0] << " " << separator << " " << rhs << std::endl;)
                }
            }

            ++lineNumber;
        }
        PAX_SETTINGS_PRINT(std::cout << "[Settings] End parsing " << path << std::endl;)
    }

    bool Settings::writeToFile(const std::string &path, bool overwrite) const {
        // Do not use std::endl to avoid flushes
        const char lineEnd = '\n';

        bool fileAreadyExists;
        {
            std::ifstream file(path);
            fileAreadyExists = file.good();
        }

        if (!fileAreadyExists || overwrite) {
            std::ofstream file(path);

            if (file) {
                for (auto &kv : settings) {
                    file << kv.first << " = " << kv.second << lineEnd;
                }

                file.close();
                return true;
            } else {
                std::cerr << "[Settings::writeToFile] Warning: Could not open " << path << "!" << std::endl;
            }
        } else {
            std::cerr << "[Settings::writeToFile] Warning: File " << path << " already exists!" << std::endl;
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
            throw std::runtime_error("Error in Settings: The variable " + varName + " has no entry!");
        }
    }

    template<>
    std::vector<std::string> Settings::getTypeVector<std::string>(const std::string &varName) const {
        std::string value = get<std::string>(varName);
        std::vector<std::string> tuple;

        if (Util::String::startsWith(value, "(") && Util::String::endsWith(value, ")")) {
            value = value.substr(1, value.size() - 2);

            size_t pos = 0;
            size_t nextComma;

            do {
                nextComma = value.find(',', pos);
                std::string valueComponent = Util::String::trimmed(value.substr(pos, nextComma - pos));
                tuple.push_back(valueComponent);

                pos = nextComma + 1;
            } while(nextComma != std::string::npos);
        } else {
            throw std::runtime_error("Error in Settings: The variable " + varName + " is not a tuple!");
        }

        return tuple;
    }
}

#undef PAX_SETTINGS_PRINT