//
// Created by Paul on 29.04.2017.
//

#ifndef PAXENGINE3_TRANSFORM_H
#define PAXENGINE3_TRANSFORM_H

#include <paxutil/lib/GlmIncludes.h>
#include <paxutil/math/Angles.h>
#include <paxutil/math/Basis.h>

namespace PAX {
    class Transformation {
    public:
        // TODO: Make this configurable
        const static Math::Basis Basis;

    private:
        union {
            glm::mat4 _relativeMat;

            struct {
                union {
                    glm::vec2 _xy;
                    glm::vec3 _xyz;
                };
                float _w;
            } _relativeMatColumn[4];
        };

        glm::quat _rotation;
        glm::vec3 _scale;

        Transformation * _parent = nullptr;

        void updateRelativeMatrix();

    public:
        Transformation();
        Transformation(const Transformation & other);
        explicit Transformation(const glm::mat4 & trafo, Transformation* parent = nullptr);
        explicit Transformation(Transformation* parent);

        const glm::vec3& position() const;
        glm::vec3& position();
        const glm::vec2& position2D() const;
        glm::vec2& position2D();
        const float& x() const;
        float& x();
        const float& y() const;
        float& y();
        const float& z() const;
        float& z();

        /// Sets updir to vertically above lookdir,
        /// \param lookdir
        void setLookDirection(const glm::vec3 &lookdir);
        void setLookDirection(const glm::vec3 &lookdir, const glm::vec3& updir);
        glm::vec3 getLookDirection() const;
        glm::vec3 getUpDirection() const;

        /// Ignores updir and instead creates one.
        /// \param theta
        /// \param phi
        void setRotation(float theta, float phi);
        void setRotation(const glm::mat3 & rotationMatrix);
        void setRotation(const glm::quat & rotation);
        void setRotation(const glm::vec3 & euler);
        void setRotation(float eulerX, float eulerY, float eulerZ);
        void setRotation2DInRadians(float radians);
        void setRotation2DInDegrees(float degrees);
        void setRotation2D(const glm::vec2 & direction);

        /// Ignores up direction! Assumes that it is straight upward.
        /// \return
        glm::vec2 getRotationAsSphericalCoordinates() const;
        const glm::quat & getRotationAsQuaternion() const;
        glm::mat3 getRotationAsMatrix() const;
        glm::vec3 getRotationAsEulerAngles() const;
        float getRotation2DInRadians() const;
        float getRotation2DInDegrees() const;
        glm::vec2 getRotation2DAsDirection() const;

        const glm::vec3 & getScale() const;
        glm::vec2 getScale2D() const;
        void setScale(const glm::vec3 & scale);
        glm::vec3 getAbsoluteScale() const;
        glm::vec2 getAbsoluteScale2D() const;

        const glm::mat4& relativeMatrix() const;
        glm::mat4& relativeMatrix();
        glm::mat4 getWorldMatrix() const;

        explicit operator glm::mat4&();
        Transformation & operator=(const glm::mat4 & mat);
        glm::mat4 operator*(const glm::mat4 & mat) const;
        void operator*=(const glm::mat4 & mat);

        void setParent(Transformation *parent);
        Transformation* getParent() const;
    };
}

#endif //PAXENGINE3_TRANSFORM_H
