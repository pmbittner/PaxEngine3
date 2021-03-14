//
// Created by Paul Bittner on 14.03.2021.
//

#ifndef PAXENGINE3_XMLBITMAPFONTLOADER_H
#define PAXENGINE3_XMLBITMAPFONTLOADER_H

#include <paxfont/bitmap/BitmapFont.h>
#include <paxutil/resources/ResourceLoader.h>

namespace PAX::Font {
    class XMLBitmapFontLoader : public ResourceLoader<BitmapFont, Path> {
    public:
        PAX_NODISCARD bool canLoad(Path p) const override;
        PAX_NODISCARD std::shared_ptr<BitmapFont> load(Path p) override;
    };
}

#endif //PAXENGINE3_XMLBITMAPFONTLOADER_H
