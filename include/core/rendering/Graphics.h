//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include <core/rendering/event/GraphicsShaderChangedEvent.h>
#include <core/event/EventHandler.h>
#include "interface/Renderable.h"
#include "../entity/EntityComponent.h"
#include "resource/Shader.h"

namespace PAX {
    PAX_EntityComponent(Graphics, false, public Renderable)
    protected:
        Shader *_shader;

    public:
        EventHandler<GraphicsShaderChangedEvent&> OnShaderChanged;

        Shader *getShader() const;
        void setShader(Shader *shader);

        virtual float getZ() override;
    };
}

#endif //PAXENGINE3_GRAPHICS_H
