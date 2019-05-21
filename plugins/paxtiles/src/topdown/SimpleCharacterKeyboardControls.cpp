//
// Created by Paul on 21.05.2019.
//

#include <paxtiles/topdown/SimpleCharacterKeyboardControls.h>

namespace PAX::Tiles {
    PAX_PROPERTY_SOURCE(SimpleCharacterKeyboardControls, PAX_PROPERTY_IS_CONCRETE)
    
    SimpleCharacterKeyboardControls * SimpleCharacterKeyboardControls::createFromProvider(PAX::ContentProvider &) {
        return new SimpleCharacterKeyboardControls();
    }
    
    void SimpleCharacterKeyboardControls::initializeFromProvider(PAX::ContentProvider & c) {
        Super::initializeFromProvider(c);
    }
}