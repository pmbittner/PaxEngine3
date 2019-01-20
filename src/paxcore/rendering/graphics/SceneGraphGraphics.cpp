//
// Created by paul on 07.01.19.
//

#include <paxcore/rendering/graphics/SceneGraphGraphics.h>

PAX_PROPERTY_SOURCE(PAX::SceneGraphGraphics, PAX_PROPERTY_IS_CONCRETE)

PAX::SceneGraphGraphics * PAX::SceneGraphGraphics::createFromProvider(PAX::ContentProvider & provider) {
    return new SceneGraphGraphics();
}

void PAX::SceneGraphGraphics::initializeFromProvider(PAX::ContentProvider & provider) {
    // TODO: Do I really want to parse a complete scenegraph from provider!?
    Super::initializeFromProvider(provider);
}