//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include <typeindex>

#include <paxcore/entity/EntityComponent.h>
#include <paxcore/event/EventHandler.h>
#include <paxcore/rendering/event/GraphicsShaderChangedEvent.h>
#include <paxcore/rendering/scenegraph/SceneGraph.h>
#include "data/Shader.h"

namespace PAX {
    class Graphics : public EntityComponent, public Renderable {
        PAX_ENTITYCOMPONENT_BODY(EntityComponent, false)
    protected:
        std::shared_ptr<Shader> _shader = nullptr;

        virtual void registerFlags(Shader::Flags &flags);

    public:
        EventHandler<GraphicsShaderChangedEvent&> OnShaderChanged;

        Shader::Flags getShaderFlags();
        std::shared_ptr<Shader>& getShader();
        virtual void setShader(std::shared_ptr<Shader> &shader);

        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_GRAPHICS_H
