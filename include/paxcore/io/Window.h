//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_WINDOW_H
#define PAXENGINE3_WINDOW_H

#include <string>
#include <paxutil/lib/GlmIncludes.h>

#include "polypropylene/event/EventHandler.h"
#include "event/ResolutionChangedEvent.h"

namespace PAX {
    class InputSystem;

    class Window {
        friend class InputSystem;

        bool _fullscreen = false;

    protected:
        glm::ivec2 _resolution;

    public:
        virtual ~Window() = default;

        EventHandler<ResolutionChangedEvent&> OnResolutionChanged;

        virtual void setResolution(const glm::ivec2 & resolution);
        virtual glm::ivec2 getResolution();

        virtual void setFullscreen(bool fullscreen);
        bool isFullscreen();

        virtual void dispose();
    };
}

#endif //PAXENGINE3_WINDOW_H
