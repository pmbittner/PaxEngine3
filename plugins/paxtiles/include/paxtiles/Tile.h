//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILE_H
#define PAXENGINE3_TILE_H

namespace PAX {
    namespace Tiles {
        struct Tile {
            int textureColumn;
            int textureRow;
            int tileSetIndex;
            bool isEmpty = false;
        };
    }
}

#endif //PAXENGINE3_TILE_H
