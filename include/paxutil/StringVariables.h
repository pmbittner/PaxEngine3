//
// Created by Bittner on 06.03.2019.
//

#ifndef PAXENGINE3_TYPES_H
#define PAXENGINE3_TYPES_H

#include <map>
#include <iostream>

namespace PAX {
    using VariableRegister = std::map<std::string, std::string>;

    struct VariableHierarchy {
        // This can contain other VariableHierarchies, too.
        VariableRegister values;
        std::map<std::string, VariableHierarchy> children;

        std::string tryGet(const std::string & val) const {
            try {
                return values.at(val);
            } catch (std::out_of_range & e) {
                std::cerr << "[VariableHierarchy::tryGet] error: " << e.what() << std::endl;
            }

            return "";
        }
    };

    class VariableResolver {
        static constexpr const char* VariableDeclarationBegin = "${";
        static constexpr const char* VariableDeclarationEnd = "}";
    public:
        static std::string resolveVariables(const std::string & str, const VariableRegister & variables);
        static void resolveAllInHierarchy(VariableHierarchy & vars, const VariableRegister & variables);
    };
}

#endif //PAXENGINE3_TYPES_H
