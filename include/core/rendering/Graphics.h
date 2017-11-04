//
// Created by Paul on 02.05.2017.
//

#ifndef PAXENGINE3_GRAPHICS_H
#define PAXENGINE3_GRAPHICS_H

#include <core/entity/EntityComponent.h>
#include <core/event/EventHandler.h>
#include <core/rendering/event/GraphicsShaderChangedEvent.h>
#include "interface/Renderable.h"
#include "resource/Shader.h"

namespace PAX {
    PAX_EntityComponent(Graphics, false, public Renderable)
    protected:
        Shader *_shader;

    public:
        EventHandler<GraphicsShaderChangedEvent&> OnShaderChanged;

        Shader *getShader() const;
        void setShader(Shader *shader);

        virtual float getZ();
    };
}

#endif //PAXENGINE3_GRAPHICS_H
