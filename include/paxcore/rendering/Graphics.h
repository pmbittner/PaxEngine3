//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include <typeindex>

#include <paxcore/gameentity/GameEntityProperty.h>
#include <polypropylene/event/EventHandler.h>
#include <paxcore/rendering/event/GraphicsShaderChangedEvent.h>
#include <paxcore/rendering/scenegraph/SceneGraph.h>
#include "data/Shader.h"

namespace PAX {
    class Graphics : public GameEntityProperty, public Renderable {
        PAX_PROPERTY(Graphics, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

    protected:
        std::shared_ptr<Shader> _shader = nullptr;

        virtual void registerFlags(Shader::Flags &flags);

    public:
        EventHandler<GraphicsShaderChangedEvent&> OnShaderChanged;

        ~Graphics() override = 0;

        Shader::Flags getShaderFlags();
        std::shared_ptr<Shader>& getShader();
        virtual void setShader(const std::shared_ptr<Shader> &shader);

        ClassMetadata getMetadata() override;

        void render(RenderOptions &renderOptions) override;
    };
}

#endif //PAXENGINE3_GRAPHICS_H
