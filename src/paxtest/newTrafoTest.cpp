#include <cmath>

//
// Created by paul on 11.09.18.
//

#include <iostream>

#include <paxutil/lib/GlmIncludes.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <paxutil/math/Angles.h>
#include <paxutil/math/Basis.h>

namespace PAX {
    class NewTrafo {
    public:
        const static Math::Basis basis;
    private:

        union {
            glm::mat4 _relativeMat;

            struct {
                glm::vec3 _xyz;
                float _w;
            } _relativeMatColumn[4];
        };

        glm::quat _rotation;
        glm::vec3 _scale;

        NewTrafo * _parent = nullptr;

        void updateRelativeMatrix() {
            glm::mat3 rotMat = getRotationAsMatrix();
            for (unsigned int column = 0; column < 3; ++column)
                _relativeMatColumn[column]._xyz = _scale[column] * rotMat[column];
        }

    public:
        explicit NewTrafo(const glm::mat4 & trafo, NewTrafo* parent = nullptr) : _relativeMat(trafo), _parent(parent) {}

        explicit NewTrafo(NewTrafo* parent) : NewTrafo(glm::mat4(1), parent) {}

        NewTrafo() : NewTrafo(nullptr) {}

        // Position
        const glm::vec3& position() const {
            return _relativeMatColumn[3]._xyz;
        }

        glm::vec3& position() {
            return _relativeMatColumn[3]._xyz;
        }

        // Rotation

        /// Sets updir to vertically above lookdir,
        /// \param lookdir
        void setLookDirection(const glm::vec3 &lookdir) {
            glm::vec2 polar = Math::lookDirToSphericalCoordinates(lookdir);
            glm::vec3 updir = Math::sphericalCoordinatesToUpDirection(polar.x, polar.y);
            setLookDirection(lookdir, updir);
        }

        void setLookDirection(const glm::vec3 &lookdir, const glm::vec3& updir) {
            setRotation(glm::quatLookAt(lookdir, updir));
        }

        glm::vec3 getLookDirection() const {
            return _rotation * basis.Forward;
        }

        glm::vec3 getUpDirection() const {
            return _rotation * basis.Up;
        }

        void setRotation(const glm::mat3 & rotationMatrix) { //d
            this->_rotation = glm::quat_cast(rotationMatrix);
            updateRelativeMatrix();
        }

        void setRotation(const glm::quat & rotation) { //d
            this->_rotation = rotation;
            updateRelativeMatrix();
        }

        /// Ignores updir and instead creates one.
        /// \param theta
        /// \param phi
        void setRotation(float theta, float phi) {
            glm::vec3 lookDir = Math::sphericalCoordinatesToDirection(theta, phi);
            glm::vec3 upDir = Math::sphericalCoordinatesToUpDirection(theta, phi);

            // TODO: Make updir configurable

            // assume lookDir and upDir are normalized

            this->_rotation = glm::quatLookAt(lookDir, upDir);

            updateRelativeMatrix();
        }

        void setRotation(float eulerX, float eulerY, float eulerZ) {
            glm::quat QuatAroundX = glm::angleAxis(eulerX, glm::vec3(1, 0, 0));
            glm::quat QuatAroundY = glm::angleAxis(eulerY, glm::vec3(0, 1, 0));
            glm::quat QuatAroundZ = glm::angleAxis(eulerZ, glm::vec3(0, 0, 1));

            this->_rotation = QuatAroundX * QuatAroundY * QuatAroundZ;
            updateRelativeMatrix();
        }

        const glm::quat & getRotationAsQuaternion() const {
            return _rotation;
        }

        glm::mat3 getRotationAsMatrix() const {
            return glm::mat3_cast(this->_rotation);
        }

        /// Ignores up direction! Assumes that it is straight upward.
        /// \return
        glm::vec2 getRotationInSphericalCoordinates() const {
            glm::vec3 lookDir = glm::axis(this->_rotation);
            return Math::lookDirToSphericalCoordinates(lookDir);
        };

        glm::vec3 getRotationInEulerAngles() const {
            return glm::eulerAngles(this->_rotation);
        };

        // Scale
        const glm::vec3 & getScale() const {
            return _scale;
        }

        void setScale(const glm::vec3 & scale) {
            _scale = scale;
            updateRelativeMatrix();
        }

        // Matrix

        const glm::mat4& relativeMatrix() const {
            return _relativeMat;
        }

        glm::mat4& relativeMatrix() {
            return _relativeMat;
        }

        glm::mat4 getWorldMatrix() const {
            if (_parent)
                return _parent->getWorldMatrix() * _relativeMat;
            return _relativeMat;
        }

        // Operators

        explicit operator glm::mat4&() {
            return _relativeMat;
        }

        NewTrafo & operator=(const glm::mat4 & mat) {
            _relativeMat = mat;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(mat, _scale, _rotation, translation, skew, perspective);
            return *this;
        }

        glm::mat4 operator*(const glm::mat4 & mat) {
            return _relativeMat * mat;
        }

        void operator*=(const glm::mat4 & mat) {
            (*this) = _relativeMat * mat;
        }

        // Parent

        void setParent(NewTrafo *parent) {
            this->_parent = parent;
        }

        NewTrafo* getParent() const {
            return this->_parent;
        }
    };

    const Math::Basis NewTrafo::basis = Math::OpenGLBasis;
}

int main(int argc, char* argv[]) {
    using namespace PAX;

    {
        NewTrafo t;
        glm::vec3 posCopy = t.position();
        glm::vec3 &posRef = t.position();
        const glm::vec3 &constPosRef = t.position();

        t.position() = {0, 0, 1};
        std::cout << t.position() << std::endl;
        t.relativeMatrix() = glm::rotate(float(M_PI_2), glm::vec3(0, 1, 0)) * t.relativeMatrix();
        std::cout << t.position() << std::endl;
    }

    { // Test rotation
        std::cout << "Test rotation" << std::endl;
        NewTrafo t;
        glm::vec3 look = glm::vec3(-1, 0, 0);
        glm::vec3 up = glm::vec3(0, 0, 1);
        std::cout << "Set Rotation to \nLook = " << look << " \n  Up = " << up << std::endl;
        t.setLookDirection(look, up);
        std::cout << "Look = " << t.getLookDirection() << "\n  Up = " << t.getUpDirection() << std::endl;
        glm::vec3 rotatedWithQuat = t.getRotationAsQuaternion() * NewTrafo::basis.Forward;
        glm::vec3 rotatedWithMat  = t.getRotationAsMatrix() * NewTrafo::basis.Forward;
        std::cout << "rotatedWithQuat = " << rotatedWithQuat << std::endl;
        std::cout << "rotatedWithMat = " << rotatedWithMat << std::endl;
    }

    { // Spherical coord test
        float t = 0;
        float p = 0;
        glm::vec3 lookDir = Math::sphericalCoordinatesToDirection(t, p);
        std::cout << "polar coordinates " << glm::vec2(t, p) << " points at direction " << lookDir << std::endl;
        std::cout << "converts back to " << Math::lookDirToSphericalCoordinates(lookDir) << std::endl;
    }
}