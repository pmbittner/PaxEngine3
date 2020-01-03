//
// Created by Paul on 09.07.2017.
//

#ifndef PAXENGINE3_RESOLUTIONCHANGEDEVENT_H
#define PAXENGINE3_RESOLUTIONCHANGEDEVENT_H

#include <paxutil/lib/GlmIncludes.h>
#include "polypropylene/event/Event.h"

namespace PAX {
    struct ResolutionChangedEvent : public Event {
        int _oldWidth, _oldHeight, _newWidth, _newHeight;

    public:
        ResolutionChangedEvent(int oldWidth, int oldHeight, int newWidth, int newHeight);
        ResolutionChangedEvent(glm::ivec2 oldRes, glm::ivec2 newRes);

        int getOldWidth();
        int getOldHeight();
        int getNewWidth();
        int getNewHeight();
    };
}

#endif //PAXENGINE3_RESOLUTIONCHANGEDEVENT_H
