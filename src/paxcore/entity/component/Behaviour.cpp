//
// Created by Paul on 19.01.2018.
//

#include <paxcore/entity/component/Behaviour.h>

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Behaviour, PAX_PROPERTY_IS_ABSTRACT)

    void Behaviour::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }

    void Behaviour::update() {

    }
}