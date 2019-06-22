//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <paxutil/lib/GlmIncludes.h>
#include <glm/detail/type_mat4x4.hpp>

#include "PerspectiveProjection.h"

#include "paxcore/entity/EntityProperty.h"
#include "../scenegraph/SceneGraph.h"
#include "../Viewport.h"
#include "../RenderOptions.h"

namespace PAX {
    class Camera : public EntityProperty, public SceneGraph {
        PAX_PROPERTY(Camera, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(EntityProperty)
        PAX_PROPERTY_IS_SINGLE

        glm::mat4 _viewMatrix = glm::mat4();
        std::shared_ptr<Viewport> _viewport;
        std::shared_ptr<Projection> _projection;

        void onViewportWidthChanged(int oldWidth, int newWidth);
        void onViewportHeightChanged(int oldHeight, int newHeight);

    public:
        Camera(const std::shared_ptr<Viewport> & viewport, const std::shared_ptr<Projection> & projection = std::make_shared<PerspectiveProjection>());

        virtual void render(RenderOptions &renderOptions) override;

        const glm::mat4 &getViewTransform();
        std::shared_ptr<Viewport> getViewport() const;
        std::shared_ptr<Projection> getProjection() const;
    };
}

#endif //PAXENGINE3_CAMERA_H
