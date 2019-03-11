//
// Created by Bittner on 07.03.2019.
//

#include <paxutil/StringVariables.h>

namespace PAX {
    std::string VariableResolver::resolveVariables(const std::string & str, const VariableRegister & variables) {
        std::string result = str;

        // str[varDecIndex] == VariableDeclaration
        std::size_t varDecIndex = result.find(VariableDeclarationBegin);
        while (varDecIndex != std::string::npos) {
            // finds first occurence and hence the end of our var
            std::size_t varDecEndIndex = result.find(VariableDeclarationEnd);

            if (varDecEndIndex == std::string::npos) {
                std::cerr << "[VariableResolver::resolveVariables] Warning: Variable declaration end missing in " << str.c_str() << std::endl;
                // terminate since we are left in an infinite loop otherwise
                break;
            } else {
                std::size_t varNameIndex  = varDecIndex + strlen(VariableDeclarationBegin);
                std::size_t varNamelength = varDecEndIndex - strlen(VariableDeclarationEnd) - varNameIndex + 1;
                std::string varName = result.substr(varNameIndex, varNamelength);
                std::string varValue;

                const auto & it = variables.find(varName);
                if (it != variables.end()) {
                    varValue = it->second;
                }

                result = result.replace(
                        varDecIndex,
                        varNamelength + strlen(VariableDeclarationBegin) + strlen(VariableDeclarationEnd),
                        varValue
                );
            }

            // search for next occurrence
            varDecIndex = result.find(VariableDeclarationBegin);
        }

        return result;
    }

    void VariableResolver::resolveAllInHierarchy(VariableHierarchy &vars, const VariableRegister &variables) {
        {
            VariableRegister::iterator it;
            for (it = vars.values.begin(); it != vars.values.end(); ++it) {
                std::string newFirst = resolveVariables(it->first, variables);
                std::string newSecond = resolveVariables(it->second, variables);
                vars.values[it->first] = newFirst;
                vars.values[it->second] = newSecond;
            }
            /*
            std::cout << "[VariableResolver::resolveAllInHierarchy] after resolve:" << std::endl;
            for (it = vars.values.begin(); it != vars.values.end(); ++it) {
                std::cout << "\t" << it->first.c_str() << " -> " << it->second.c_str() << std::endl;
            }//*/
        }
        {
            std::map<std::string, VariableHierarchy>::iterator it;
            for (it = vars.children.begin(); it != vars.children.end(); ++it) {
                resolveAllInHierarchy(it->second, variables);
            }
        }
    }
}