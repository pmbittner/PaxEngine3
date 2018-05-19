//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_WINDOW_H
#define PAXENGINE3_WINDOW_H

#include <string>
#include <glm/glm.hpp>

#include "../event/EventHandler.h"
#include "event/ResolutionChangedEvent.h"

namespace PAX {
    class Window {
        bool _fullscreen;

    public:
        virtual ~Window() {};

        EventHandler<ResolutionChangedEvent&> OnResolutionChanged;

        virtual glm::ivec2 getResolution() = 0;

        virtual void setFullscreen(bool fullscreen);
        bool isFullscreen();
    };
}

#endif //PAXENGINE3_WINDOW_H
