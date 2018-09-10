//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_TRANSFORM_H
#define PAXENGINE3_TRANSFORM_H

#include <vector>
#include <paxutil/lib/GlmIncludes.h>

namespace PAX {
    class Entity;

    class Transform {
        friend class Entity;

    private:
        union {
            glm::vec2 _pos2D;
            glm::vec3 _pos3D;
        };

        union {
            glm::vec2 _scale2D;
            glm::vec3 _scale3D;
        };

        // rotation around z axis is rotation2D
        glm::vec3 _rotation;

        glm::mat4 _relativeTransform;
        glm::mat4 _worldTransform;

        Transform *_parent = nullptr;
        Entity *entity = nullptr;
        std::vector<Transform*> _children;

        bool _relativeMatDirty;
        bool _worldMatDirty;

        void setRelativeMatDirty(bool dirty);
        void setWorldMatDirty(bool dirty);

    public:
        Transform();

        /** GETTERS AND SETTERS **/

        // Parent
        void setParent(Transform *parent);
        Transform* getParent();

        // Position

        float getX() const;
        float getY() const;
        float getZ() const;
        glm::vec2 getPosition2D() const;
        glm::vec3 getPosition() const;
        float getAbsoluteX() const;
        float getAbsoluteY() const;
        float getAbsoluteZ() const;
        glm::vec2 getAbsolutePosition2D() const;
        glm::vec3 getAbsolutePosition() const;

        float& x();
        float& y();
        float& z();
        glm::vec2& position2D();
        glm::vec3& position();

        // Rotation
        float getRotation2D() const;
        glm::vec3 getRotation() const;
        float getAbsoluteRotation2D() const;
        glm::vec3 getAbsoluteRotation() const;

        float& rotation2D();
        glm::vec3& rotation();

        // Scale
        float getScaleX() const;
        float getScaleY() const;
        float getScaleZ() const;
        glm::vec2 getScale2D() const;
        glm::vec3 getScale() const;

        float getAbsoluteScaleX() const;
        float getAbsoluteScaleY() const;
        float getAbsoluteScaleZ() const;
        glm::vec2 getAbsoluteScale2D() const;
        glm::vec3 getAbsoluteScale() const;

        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);
        void setScale(float x, float y);
        void setScale(const glm::vec2& scale);
        void setScale(float x, float y, float z);
        void setScale(const glm::vec3& scale);

        // Mat
        const glm::mat4 &toRelativeMatrix();
        const glm::mat4 &toWorldMatrix();
    };
}

#endif //PAXENGINE3_TRANSFORM_H
