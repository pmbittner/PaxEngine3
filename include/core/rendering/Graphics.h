//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include "Renderable.h"
#include "../entity/EntityComponent.h"
#include "scenegraph/SceneGraphGeneratable.h"

namespace PAX {
    PAX_EntityComponent(Graphics, false, public Renderable, public SceneGraphGeneratable)
    public:
        virtual float getZ() override;
    };
}

#endif //PAXENGINE3_GRAPHICS_H
