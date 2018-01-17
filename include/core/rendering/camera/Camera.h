//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>

#include "../scenegraph/SceneGraph.h"
#include "../../entity/EntityComponent.h"
#include "PerspectiveProjection.h"
#include "../Viewport.h"
#include "../RenderOptions.h"

namespace PAX {
    PAX_ENTITYCOMPONENT(Camera, false)
    class Camera : public EntityComponent, public SceneGraph {

        PAX_ENTITYCOMPONENT_BODY(Camera)

        glm::mat4 _viewMatrix;
        Viewport *_viewport;
        Projection *_projection;

        void onViewportWidthChanged(int oldWidth, int newWidth);
        void onViewportHeightChanged(int oldHeight, int newHeight);

    public:
        Camera(Viewport *viewport, Projection *projection = new PerspectiveProjection());

        virtual void render(RenderOptions &renderOptions) override;

        const glm::mat4 &getViewTransform();
        Viewport* getViewport();
        Projection* getProjection();
    };
}

#endif //PAXENGINE3_CAMERA_H
