//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <paxutil/lib/GlmIncludes.h>
#include <glm/detail/type_mat4x4.hpp>

#include "PerspectiveProjection.h"

#include "../../entity/EntityComponent.h"
#include "../scenegraph/SceneGraph.h"
#include "../Viewport.h"
#include "../RenderOptions.h"

namespace PAX {
    class Camera : public EntityComponent, public SceneGraph {
    PAX_PROPERTY_DERIVES(EntityComponent)
    PAX_PROPERTY_IS_SINGLE

        glm::mat4 _viewMatrix;
        std::shared_ptr<Viewport> _viewport;
        std::shared_ptr<Projection> _projection;

        void onViewportWidthChanged(int oldWidth, int newWidth);
        void onViewportHeightChanged(int oldHeight, int newHeight);

    public:
        Camera(std::shared_ptr<Viewport> viewport, std::shared_ptr<Projection> projection = std::make_shared<PerspectiveProjection>());

        virtual void render(RenderOptions &renderOptions) override;

        const glm::mat4 &getViewTransform();
        std::shared_ptr<Viewport> getViewport() const;
        std::shared_ptr<Projection> getProjection() const;
    };
}

#endif //PAXENGINE3_CAMERA_H
