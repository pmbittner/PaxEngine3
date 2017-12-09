//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_TRANSFORM_H
#define PAXENGINE3_TRANSFORM_H

#include <vector>
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

        Transform *_parent = nullptr;
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
        /*
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void setPosition(float x, float y);
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec2 pos);
        void setPosition(glm::vec3 pos);
         */

        float getX();
        float getY();
        float getZ();
        glm::vec2 getPosition2D();
        glm::vec3 getPosition();

        float& x();
        float& y();
        float& z();
        glm::vec2& position2D();
        glm::vec3& position();

        // Rotation
        /*
        void setRotation(float rotation);
        void setRotation(float x, float y, float z);
        void setRotation(glm::vec3 rotation);
         */
        float getRotation2D();
        glm::vec3 getRotation();

        float& rotation2D();
        glm::vec3& rotation();

        // Scale
        /*
        void setScaleX(float x);
        void setScaleY(float y);
        void setScaleZ(float z);
        void setScale(float x, float y);
        void setScale(float x, float y, float z);
        void setScale(glm::vec3 scale);
         */
        float getScaleX();
        float getScaleY();
        float getScaleZ();
        glm::vec2 getScale2D();
        glm::vec3 getScale();

        float& scaleX();
        float& scaleY();
        float& scaleZ();
        glm::vec2& scale2D();
        glm::vec3& scale();

        // Mat
        const glm::mat4 &toRelativeMatrix();
        const glm::mat4 &toWorldMatrix();
    };
}

#endif //PAXENGINE3_TRANSFORM_H
