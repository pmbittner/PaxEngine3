//
// Created by Paul Bittner on 30.01.2021.
//

#ifndef MESHFOLD_ABILITYIDENTIFIER_H
#define MESHFOLD_ABILITYIDENTIFIER_H

namespace PAX {
    using AbilityIdentifier = std::string;
    enum class AbilityResult {
        Success = 0,
        Failure,
        NoSuchAbility
    };
}

#endif //MESHFOLD_ABILITYIDENTIFIER_H
