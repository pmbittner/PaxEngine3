//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include "Renderable.h"
#include "../entity/EntityComponent.h"
#include "scenegraph/SceneGraphBuildingRule.h"

namespace PAX {
    class Graphics : public Renderable, public EntityComponent {
    public:
        SceneGraphBuildingRule* getSceneGraphBuildingRule();
    };
}

#endif //PAXENGINE3_GRAPHICS_H
