//
// Created by paul on 03.01.19.
//

#ifndef PAXENGINE3_TILE_H
#define PAXENGINE3_TILE_H

namespace PAX::Tiles {
    struct TileInfo {
        bool isSolid = false;
    };

    struct Tile {
        int tileSetIndex = -1;
        int textureColumn = 0;
        int textureRow = 0;
        bool isEmpty = false;
    };
}

#endif //PAXENGINE3_TILE_H
