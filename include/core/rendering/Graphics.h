//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include <core/entity/EntityComponent.h>
#include <core/event/EventHandler.h>
#include <core/rendering/event/GraphicsShaderChangedEvent.h>
#include <core/rendering/scenegraph/SceneGraph.h>
#include "resource/Shader.h"

namespace PAX {
    PAX_EntityComponent(Graphics, false, public Renderable)
    protected:
        std::shared_ptr<Shader> _shader = nullptr;

    public:
        EventHandler<GraphicsShaderChangedEvent&> OnShaderChanged;

        std::shared_ptr<Shader>& getShader();
        void setShader(const std::shared_ptr<Shader> &shader);

        void render(RenderOptions &renderOptions) override;
    };

    typedef TypedSceneGraph<Graphics> GraphicsSceneGraph;
}

#endif //PAXENGINE3_GRAPHICS_H
