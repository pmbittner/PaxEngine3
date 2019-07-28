//
// Created by Paul on 24.01.2018.
//

#ifndef PAXENGINE3_BOX2DUTILS_H
#define PAXENGINE3_BOX2DUTILS_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include <Box2D/Box2D.h>
#include <paxcore/entity/MotionType.h>

namespace PAX::Physics {
    glm::vec2 toGLM(const b2Vec2 & b2vec);
    b2Vec2 toBox2D(const glm::vec2 &glmvec);
    b2Vec2 toBox2D(const glm::vec3 &glmvec);

    b2Shape * toBox2D(const Shape2D * shape);
    b2BodyType toBox2D(MotionType motionType);
}

#endif //PAXENGINE3_BOX2DUTILS_H
