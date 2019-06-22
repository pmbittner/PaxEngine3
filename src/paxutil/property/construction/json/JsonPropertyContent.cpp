//
// Created by Paul on 02.03.2019.
//

#include <paxutil/property/construction/json/JsonPropertyContent.h>

namespace PAX {
    namespace Json {
        JsonPropertyContent::JsonPropertyContent(const nlohmann::json &node)
                : Internal::PropertyContent(), node(node) {}

        JsonPropertyContent::~JsonPropertyContent() = default;

        bool JsonPropertyContent::has(const std::string &name) {
            return node.count(name) > 0;
        }

        std::string JsonPropertyContent::getValue(const std::string &key) {
            if (node[key].is_string()) {
                return node[key];
            }

            //std::cout << "[JsonPropertyContent::getValue] " << key << " -> ";
            std::stringstream ss;
            ss << node[key];
            //std::cout << ss.str() << std::endl;
            return ss.str();
        }

        static void buildVariableHierarchy(VariableHierarchy &h, nlohmann::json &node) {
            for (auto &entry : node.items()) {
                if (entry.value().is_string()) {
                    h.values[entry.key()] = entry.value();
                    //std::cout << "\t" << entry.key() << " -> " << entry.value() << std::endl;
                } else {
                    h.children[entry.key()] = VariableHierarchy();
                    buildVariableHierarchy(h.children[entry.key()], entry.value());
                }
            }
        }

        VariableHierarchy JsonPropertyContent::getResourceParametersFor(const std::string &name) {
            nlohmann::json &child = node[name];
            VariableHierarchy params;

            //std::cout << "[JsonPropertyContent::getResourceParametersFor] " << name << std::endl;

            buildVariableHierarchy(params, child);

            return params;
        }
    }
}