//
// Created by paul on 09.01.19.
//

#include <paxutil/property/construction/ContentProvider.h>

namespace PAX::Internal {
    template<>
    std::string PropertyContent::get<std::string>(const std::string &name, const VariableRegister &variables) {
        return getValue(name, variables);
    }
}