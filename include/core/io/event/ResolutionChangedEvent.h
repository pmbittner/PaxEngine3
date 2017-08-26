//
// Created by Paul on 09.07.2017.
//

#ifndef PAXENGINE3_RESOLUTIONCHANGEDEVENT_H
#define PAXENGINE3_RESOLUTIONCHANGEDEVENT_H

#include <glm/vec2.hpp>
#include "../../event/Event.h"

namespace PAX {
    class ResolutionChangedEvent : public Event {
        int _oldWidth, _oldHeight, _newWidth, _newHeight;

    public:
        ResolutionChangedEvent(int oldWidth, int oldHeight, int newWidth, int newHeight);
        ResolutionChangedEvent(glm::vec2 oldRes, glm::vec2 newRes);

        int getOldWidth();
        int getOldHeight();
        int getNewWidth();
        int getNewHeight();
    };
}

#endif //PAXENGINE3_RESOLUTIONCHANGEDEVENT_H
