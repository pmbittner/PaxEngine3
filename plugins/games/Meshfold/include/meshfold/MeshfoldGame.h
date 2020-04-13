//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PAXTILEDEMO_H
#define PAXENGINE3_PAXTILEDEMO_H

#include <paxcore/Game.h>
#include <paxcore/Engine.h>
#include <paxcore/io/event/KeyPressedEvent.h>

#include "polypropylene/log/Log.h"

#include <paxcore/world/property/WorldSize.h>

#include <paxcore/gameentity/GameEntity.h>
#include <paxcore/gameentity/property/behaviours/NoClipControls.h>

#include <paxcore/rendering/graphics/AssetGraphics.h>
#include <paxcore/rendering/graphics/SceneGraphGraphics.h>
#include <paxcore/rendering/geometry/ScreenFillingQuad.h>

#include <paxcore/rendering/factory/ViewportFactory.h>
#include <paxcore/rendering/renderpass/RenderPassFactory.h>
#include <paxcore/rendering/data/Material.h>

#include "Meshfold.h"

namespace PAX {
    class MeshfoldGame : public Game {
        World * uv_world   = nullptr;
        World * mesh_world = nullptr;
        World * screen_world = nullptr;

        RenderPass * uvRenderPass = nullptr;

        Settings settings;

        void toggleShowUVWorld();

    public:
        void initialize() override;
        void terminate() override;

        void onKeyDown(KeyPressedEvent & keyPressedEvent);
    };
}

#endif //PAXENGINE3_PAXTILEDEMO_H
