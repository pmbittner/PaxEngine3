//
// Created by paul on 07.01.19.
//

#ifndef PAXENGINE3_SCENEGRAPHGENERATORFACTORY_H
#define PAXENGINE3_SCENEGRAPHGENERATORFACTORY_H

#include "SceneGraphGenerator.h"

namespace PAX {
    class SceneGraphGeneratorFactory {
    public:
        virtual SceneGraphGenerator * create(int dimensions) = 0;
    };
}

#endif //PAXENGINE3_SCENEGRAPHGENERATORFACTORY_H
