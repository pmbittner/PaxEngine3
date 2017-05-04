//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_TRANSFORM_H
#define PAXENGINE3_TRANSFORM_H

#include <glm/glm.hpp>

namespace PAX {
    class Transform {
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

        Transform *_parent;
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
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void setPosition(float x, float y);
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec2 pos);
        void setPosition(glm::vec3 pos);

        float x();
        float y();
        float z();
        glm::vec2 xy();
        glm::vec3 xyz();

        // Rotation
        void setRotation(float rotation);
        void setRotation(float x, float y, float z);
        void setRotation(glm::vec3 rotation);

        float getRotation();
        glm::vec3 getRotation3D();

        // Scale
        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);
        void setScale(float x, float y);
        void setScale(float x, float y, float z);
        void setScale(glm::vec3 scale);

        float getScaleX();
        float getScaleY();
        float getScaleZ();
        glm::vec2 getScale();
        glm::vec3 getScale3D();

        // Mat
        const glm::mat4 &toRelativeMatrix();
        const glm::mat4 &toWorldMatrix();
    };
}

#endif //PAXENGINE3_TRANSFORM_H
