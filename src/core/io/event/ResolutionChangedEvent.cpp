//
// Created by Paul on 09.07.2017.
//

#include "../../../../include/core/io/event/ResolutionChangedEvent.h"

namespace PAX {
    ResolutionChangedEvent::ResolutionChangedEvent(int oldWidth, int oldHeight, int newWidth, int newHeight) :
            _oldWidth(oldWidth), _oldHeight(oldHeight), _newWidth(newWidth), _newHeight(newHeight) {}

    ResolutionChangedEvent::ResolutionChangedEvent(glm::vec2 oldRes, glm::vec2 newRes) :
            _oldWidth(oldRes.x), _oldHeight(oldRes.y), _newWidth(newRes.x), _newHeight(newRes.y) {}

    int ResolutionChangedEvent::getOldWidth() { return _oldWidth; }
    int ResolutionChangedEvent::getOldHeight() { return _oldHeight; }
    int ResolutionChangedEvent::getNewWidth() { return _newWidth; }
    int ResolutionChangedEvent::getNewHeight() { return _newHeight; }
}