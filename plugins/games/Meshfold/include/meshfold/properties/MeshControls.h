//
// Created by Paul Bittner on 13.04.2020.
//

#ifndef PAXENGINE3_MESHCONTROLS_H
#define PAXENGINE3_MESHCONTROLS_H

#include <paxcore/world/WorldProperty.h>
#include <paxcore/io/event/MouseButtonPressedEvent.h>
#include <paxcore/io/event/MouseButtonReleasedEvent.h>
#include <paxcore/io/event/MouseWheelEvent.h>
#include <paxcore/io/event/MouseMovedEvent.h>

namespace PAX {
    class MeshControls : public WorldProperty {
        PAX_PROPERTY(MeshControls, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(WorldProperty)
        PAX_PROPERTY_IS_SINGLE

        GameEntity * exhibit = nullptr;
        GameEntity * camera = nullptr;
        float mouseSensivityInRadiansPerPixel = 0.01;
        float scrollSensivity = 0.1;
        glm::vec2 totalRot = {0, 0};

    public:
        void setExhibit(GameEntity * exhibit);
        void setCamera(GameEntity * camera);

        void attached(World & w) override;
        void detached(World & w) override;

        void onMouseDragged(MouseMovedEvent& e);
        void onMousePressed(MouseButtonPressedEvent& e);
        void onMouseReleased(MouseButtonReleasedEvent& e);
        void onMouseWheel(MouseWheelEvent& e);

        ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_MESHCONTROLS_H
