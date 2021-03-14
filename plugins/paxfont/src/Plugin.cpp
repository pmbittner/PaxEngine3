//
// Created by Paul on 13.08.2018.
//

#include "paxfont/Plugin.h"
#include "paxfont/bitmap/BitmapText.h"
#include "polypropylene/property/PropertyFactory.h"

namespace PAX::Font {
    void Plugin::registerResourceLoaders(Resources &resources) {
        resources.registerLoader(&xmlBitmapFontLoader);
    }

    void Plugin::registerJsonWriters(::PAX::Json::JsonFieldWriterRegister &writerRegister) {
        bitmapFontJsonResourceWriter.registerAt(writerRegister);
    }

    void Plugin::registerProperties() {
        PAX_PROPERTY_REGISTER(BitmapText);
    }
}