//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>
#include "../entity/EntityComponent.h"
#include "../rendering/scenegraph/SceneGraph.h"
#include "Viewport.h"

namespace PAX {
    PAX_EntityComponent(Camera, false, public SceneGraph)
        glm::mat4 _viewMatrix;
        Viewport *_viewport;

    public:
        Camera(Viewport *viewport);

        virtual void render() override;
        const glm::mat4 &getViewTransform();
        Viewport* getViewport();
    };
}

#endif //PAXENGINE3_CAMERA_H
