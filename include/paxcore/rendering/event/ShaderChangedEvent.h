//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_SHADERCHANGEDEVENT_H
#define PAXENGINE3_SHADERCHANGEDEVENT_H

#include <memory>
#include <paxutil/event/Event.h>

namespace PAX {
    class Shader;
    struct ShaderChangedEvent : public Event {
    public:
        const std::shared_ptr<Shader> oldShader, newShader;

        ShaderChangedEvent(const std::shared_ptr<Shader> &oldShader, const std::shared_ptr<Shader> &newShader)
                : oldShader(oldShader), newShader(newShader)
        {}
    };
}

#endif //PAXENGINE3_SHADERCHANGEDEVENT_H
