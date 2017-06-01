//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_CAMERA_H
#define PAXENGINE3_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>

#include "../entity/EntityComponent.h"

namespace PAX {
    PAX_EntityComponent(Camera, false)
        glm::mat4 _viewMatrix;

    public:
        const glm::mat4 &getViewTransform();
    };
}

#endif //PAXENGINE3_CAMERA_H
