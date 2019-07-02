//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILE_H
#define PAXENGINE3_TILE_H

namespace PAX {
    namespace Tiles {
        struct Tile {
            int textureColumn = 0;
            int textureRow = 0;
            int tileSetIndex = -1;
            bool isEmpty = false;


        };
    }
}

#endif //PAXENGINE3_TILE_H
