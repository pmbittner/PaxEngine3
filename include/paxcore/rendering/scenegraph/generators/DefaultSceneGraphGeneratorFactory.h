//
// Created by Bittner on 10/07/2019.
//

#ifndef PAXENGINE3_DEFAULTSCENEGRAPHGENERATORFACTORY_H
#define PAXENGINE3_DEFAULTSCENEGRAPHGENERATORFACTORY_H

#include "SceneGraphGeneratorFactory.h"

namespace PAX {
    class DefaultSceneGraphGeneratorFactory : public SceneGraphGeneratorFactory {
    public:
        std::shared_ptr<SceneGraphGenerator> create(int dimensions) override;
    };
}

#endif //PAXENGINE3_DEFAULTSCENEGRAPHGENERATORFACTORY_H
