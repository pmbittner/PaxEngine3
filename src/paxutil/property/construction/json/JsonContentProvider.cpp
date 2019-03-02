//
// Created by Paul on 02.03.2019.
//

#include <paxutil/property/construction/json/JsonContentProvider.h>

namespace PAX {
    JsonContentProvider::JsonContentProvider(const nlohmann::json &node) : ContentProvider(), node(node) {}

    JsonContentProvider::~JsonContentProvider() = default;

    std::any JsonContentProvider::provide(const std::string &name, const PAX::TypeHandle &type) {
        return {};
    }

    std::any JsonContentProvider::provideEncapsulated(const std::string &name, const PAX::TypeHandle &elementType,
                                                      const PAX::TypeHandle &containerType) {
        return {};
    }
}