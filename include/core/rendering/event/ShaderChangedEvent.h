//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_SHADERCHANGEDEVENT_H
#define PAXENGINE3_SHADERCHANGEDEVENT_H

#include <core/event/Event.h>

namespace PAX {
    class Shader;
    class ShaderChangedEvent : public Event {
    public:
        Shader *oldShader, *newShader;

        ShaderChangedEvent(Shader* oldShader, Shader* newShader) : oldShader(oldShader), newShader(newShader) {}
    };
}

#endif //PAXENGINE3_SHADERCHANGEDEVENT_H
