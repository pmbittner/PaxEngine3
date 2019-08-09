//
// Created by Paul on 28.07.2019.
//

#include <paxphysics/2d/box2d/Box2DUtils.h>
#include <paxutil/macros/MacroIncludes.h>
#include <paxphysics/2d/shape/Rectangle.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

namespace PAX::Physics {
    b2Vec2 toBox2D(const glm::vec2 & glmvec) {
        return {glmvec.x, glmvec.y};
    }

    b2Vec2 toBox2D(const glm::vec3 & glmvec) {
        return {glmvec.x, glmvec.y};
    }

    glm::vec2 toGLM(const b2Vec2 & b2vec) {
        return {b2vec.x, b2vec.y};
    }

    b2Shape * toBox2D(const Shape2D * shape, float metersPerPixel) {
        b2Shape * ret = nullptr;

        if (auto * rect = dynamic_cast<const Rectangle*>(shape)) {
            const FloatBoundingBox2D & aabb = rect->getAABB();

            auto * rectShape = new b2PolygonShape();
            // void SetAsBox(float32 hx, float32 hy, const b2Vec2& center, float32 angle);
            rectShape->SetAsBox(
                    metersPerPixel * aabb.getLength(0) / 2.f,
                    metersPerPixel * aabb.getLength(1) / 2.f,
                    toBox2D(metersPerPixel * aabb.getCenter()),
                    0);
            ret = rectShape;
        }

        if (!ret) {
            PAX_THROW_RUNTIME_ERROR("Cannot convert given shape to Box2D!");
        }

        return ret;
    }

    b2BodyType toBox2D(MotionType motionType) {
        switch (motionType) {
            case MotionType::Static: {
                return b2_staticBody;
            }

            case MotionType::Kinematic: {
                return b2_kinematicBody;
            }

            case MotionType::Dynamic: {
                return b2_dynamicBody;
            }

            default: {
                PAX_THROW_RUNTIME_ERROR("Cannot convert Entity::MotionType " << int(motionType) << " to b2BodyType");
            }
        }
    }
}