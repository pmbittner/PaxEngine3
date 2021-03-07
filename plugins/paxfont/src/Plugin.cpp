//
// Created by Paul on 13.08.2018.
//

#include "paxfont/Plugin.h"
#include "polypropylene/property/PropertyFactory.h"

#include "paxfont/monospace/Text.h"

namespace PAX::Font {
    void Plugin::registerProperties() {
        PAX_PROPERTY_REGISTER(Text);
        PAX_PROPERTY_REGISTER(Letter);
    }
}