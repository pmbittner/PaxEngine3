//
// Created by Paul on 01.05.2017.
//

#include <paxutil/math/Transformation.h>
#include <glm/gtx/matrix_decompose.hpp>

namespace PAX {
    const Math::Basis Transformation::Basis = Math::OpenGLBasis;

    void Transformation::updateRelativeMatrix() {
        glm::mat3 rotMat = getRotationAsMatrix();
        for (unsigned int column = 0; column < 3; ++column)
            _relativeMatColumn[column]._xyz = _scale[column] * rotMat[column];
    }

    Transformation::Transformation(const glm::mat4 & trafo, Transformation* parent) : _parent(parent) {
        (*this) = trafo;
    }

    Transformation::Transformation(Transformation* parent) : Transformation(glm::mat4(1), parent) {}

    Transformation::Transformation() : Transformation(nullptr) {}

    Transformation::Transformation(const Transformation & other) : Transformation(other._relativeMat, other._parent) {}

    const glm::vec3& Transformation::position() const {
        return _relativeMatColumn[3]._xyz;
    }

    glm::vec3& Transformation::position() {
        return _relativeMatColumn[3]._xyz;
    }

    const glm::vec2& Transformation::position2D() const {
        return _relativeMatColumn[3]._xy;
    }

    glm::vec2& Transformation::position2D() {
        return _relativeMatColumn[3]._xy;
    }

    const float& Transformation::x() const {
        return _relativeMatColumn[3]._xyz.x;
    }

    float& Transformation::x() {
        return _relativeMatColumn[3]._xyz.x;
    }

    const float& Transformation::y() const {
        return _relativeMatColumn[3]._xyz.y;
    }

    float& Transformation::y() {
        return _relativeMatColumn[3]._xyz.y;
    }

    const float& Transformation::z() const {
        return _relativeMatColumn[3]._xyz.z;
    }

    float& Transformation::z() {
        return _relativeMatColumn[3]._xyz.z;
    }

    void Transformation::setLookDirection(const glm::vec3 &lookdir) {
        glm::vec2 polar = Math::lookDirToSphericalCoordinates(lookdir);
        glm::vec3 updir = Math::sphericalCoordinatesToUpDirection(polar.x, polar.y);
        setLookDirection(lookdir, updir);
    }

    void Transformation::setLookDirection(const glm::vec3 &lookdir, const glm::vec3& updir) {
        setRotation(glm::quatLookAt(lookdir, updir));
    }

    glm::vec3 Transformation::getLookDirection() const {
        return _rotation * Basis.Forward;
    }

    glm::vec3 Transformation::getUpDirection() const {
        return _rotation * Basis.Up;
    }

    void Transformation::setRotation(const glm::mat3 & rotationMatrix) { //d
        this->_rotation = glm::quat_cast(rotationMatrix);
        updateRelativeMatrix();
    }

    void Transformation::setRotation(const glm::quat & rotation) { //d
        this->_rotation = rotation;
        updateRelativeMatrix();
    }

    void Transformation::setRotation(float theta, float phi) {
        glm::vec3 lookDir = Math::sphericalCoordinatesToDirection(theta, phi);
        glm::vec3 upDir = Math::sphericalCoordinatesToUpDirection(theta, phi);

        // TODO: Make updir configurable

        // assume lookDir and upDir are normalized

        this->_rotation = glm::quatLookAt(lookDir, upDir);

        updateRelativeMatrix();
    }

    void Transformation::setRotation(float eulerX, float eulerY, float eulerZ) {
        glm::quat QuatAroundX = glm::angleAxis(eulerX, glm::vec3(1, 0, 0));
        glm::quat QuatAroundY = glm::angleAxis(eulerY, glm::vec3(0, 1, 0));
        glm::quat QuatAroundZ = glm::angleAxis(eulerZ, glm::vec3(0, 0, 1));

        this->_rotation = QuatAroundX * QuatAroundY * QuatAroundZ;
        updateRelativeMatrix();
    }

    const glm::quat & Transformation::getRotationAsQuaternion() const {
        return _rotation;
    }

    glm::mat3 Transformation::getRotationAsMatrix() const {
        return glm::mat3_cast(this->_rotation);
    }

    glm::vec2 Transformation::getRotationAsSphericalCoordinates() const {
        glm::vec3 lookDir = glm::axis(this->_rotation);
        return Math::lookDirToSphericalCoordinates(lookDir);
    };

    glm::vec3 Transformation::getRotationAsEulerAngles() const {
        return glm::eulerAngles(this->_rotation);
    };

    const glm::vec3 & Transformation::getScale() const {
        return _scale;
    }

    void Transformation::setScale(const glm::vec3 & scale) {
        _scale = scale;
        updateRelativeMatrix();
    }

    glm::vec3 Transformation::getAbsoluteScale() const {
        return _parent ? _parent->getAbsoluteScale() * _scale : _scale;
    }

    const glm::mat4& Transformation::relativeMatrix() const {
        return _relativeMat;
    }

    glm::mat4& Transformation::relativeMatrix() {
        return _relativeMat;
    }

    glm::mat4 Transformation::getWorldMatrix() const {
        if (_parent)
            return _parent->getWorldMatrix() * _relativeMat;
        return _relativeMat;
    }

    Transformation::operator glm::mat4&() {
        return _relativeMat;
    }

    Transformation & Transformation::operator=(const glm::mat4 & mat) {
        _relativeMat = mat;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(mat, _scale, _rotation, translation, skew, perspective);
        return *this;
    }

    glm::mat4 Transformation::operator*(const glm::mat4 & mat) {
        return _relativeMat * mat;
    }

    void Transformation::operator*=(const glm::mat4 & mat) {
        (*this) = _relativeMat * mat;
    }

    void Transformation::setParent(Transformation *parent) {
        this->_parent = parent;
    }

    Transformation* Transformation::getParent() const {
        return this->_parent;
    }
};