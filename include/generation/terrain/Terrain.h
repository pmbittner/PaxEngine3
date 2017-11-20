//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_TERRAIN_H
#define PAXENGINE3_TERRAIN_H

#include <core/rendering/TexturedMesh.h>

namespace PAX {
    class Terrain : public Graphics {
    private:
        TexturedMesh *mesh;

    public:
        Terrain();
    };
}

#endif //PAXENGINE3_TERRAIN_H
