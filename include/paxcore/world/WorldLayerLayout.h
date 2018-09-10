//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_WORLDLAYERLAYOUT_H
#define PAXENGINE3_WORLDLAYERLAYOUT_H

#include <glm/glm.hpp>

namespace PAX {
    class WorldLayerLayout {
        virtual glm::vec2 layoutPos2PixelPos(glm::vec2);

        virtual glm::vec2 pixelPos2LayoutPos(glm::vec2);
    };
}

#endif //PAXENGINE3_WORLDLAYERLAYOUT_H
