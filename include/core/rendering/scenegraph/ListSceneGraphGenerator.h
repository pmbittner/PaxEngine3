//
// Created by Paul on 04.06.2017.
//

#ifndef PAXENGINE3_LISTSCENEGRAPHGENERATOR_H
#define PAXENGINE3_LISTSCENEGRAPHGENERATOR_H

#include "SceneGraphGenerator.h"

namespace PAX {
    class ListSceneGraphGenerator : public SceneGraphGenerator {
        std::unordered_map<Graphics*, SceneGraph*> _gfxToSceneGraph;
    public:
        virtual void addGraphics(Graphics *g) override;
        virtual void removeGraphics(Graphics *g) override;
    };
}

#endif //PAXENGINE3_LISTSCENEGRAPHGENERATOR_H
