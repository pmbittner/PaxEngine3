//
// Created by Paul on 19.01.2018.
//

#include <paxcore/entity/property/Behaviour.h>

namespace PAX {
    PAX_PROPERTY_INIT(PAX::Behaviour, PAX_PROPERTY_IS_ABSTRACT)

    void Behaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}