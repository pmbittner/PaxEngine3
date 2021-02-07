//
// Created by Paul on 24.01.2018.
//

#ifndef PAXENGINE3_BOX2DUTILS_H
#define PAXENGINE3_BOX2DUTILS_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include <Box2D/Box2D.h>
#include <paxcore/gameentity/MotionType.h>

namespace PAX::Physics {
    glm::vec2 ToGLM(const b2Vec2 & b2vec);
    b2Vec2 ToBox2D(const glm::vec2 &glmvec);
    b2Vec2 ToBox2D(const glm::vec3 &glmvec);

    b2Shape * ToBox2D(const Shape2D & shape, float metersPerPixel);
    b2BodyType ToBox2D(MotionType motionType);
}

#endif //PAXENGINE3_BOX2DUTILS_H
