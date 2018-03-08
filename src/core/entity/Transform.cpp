//
// Created by Paul on 01.05.2017.
//

#include <core/entity/Entity.h>
#include <core/entity/event/ScaleChangedEvent.h>
#include "../../../include/core/entity/Transform.h"
#include "utility/stdutils/CollectionUtils.h"

namespace PAX {
    Transform::Transform() :
            _parent(nullptr),
            _relativeMatDirty(true), _worldMatDirty(true)
    {
        _pos3D = glm::vec3(0, 0, 0);
        _rotation = glm::vec3(0, 0, 0);
        _scale3D = glm::vec3(1, 1, 1);
    }

    /** GETTERS AND SETTERS **/

    void Transform::setRelativeMatDirty(bool dirty) {
        _relativeMatDirty = dirty;

        if (_relativeMatDirty) {
            setWorldMatDirty(true);
        }
    }

    void Transform::setWorldMatDirty(bool dirty) {
        _worldMatDirty = dirty;

        if (_worldMatDirty) {
            for (Transform* child : _children)
                child->setWorldMatDirty(true);
        }
    }


    void Transform::setParent(Transform *parent) {
        if (_parent != parent) {
            if (_parent)
                Util::removeFromVector(_parent->_children, this);

            _parent = parent;

            if (_parent)
                _parent->_children.push_back(this);

            setWorldMatDirty(true);
        }
    }

    Transform* Transform::getParent() {
        return _parent;
    }


    // Position
    float Transform::getX() const {
        return _pos3D.x;
    }

    float Transform::getY() const {
        return _pos3D.y;
    }

    float Transform::getZ() const {
        return _pos3D.z;
    }

    glm::vec2 Transform::getPosition2D() const {
       return _pos2D;
    }

    glm::vec3 Transform::getPosition() const {
        return _pos3D;
    }

    float Transform::getAbsoluteX() const {
        return (_parent ? _parent->getAbsoluteX() : 0) + _pos3D.x;
    }

    float Transform::getAbsoluteY() const {
        return (_parent ? _parent->getAbsoluteY() : 0) + _pos3D.y;
    }

    float Transform::getAbsoluteZ() const {
        return (_parent ? _parent->getAbsoluteZ() : 0) + _pos3D.z;
    }

    glm::vec2 Transform::getAbsolutePosition2D() const {
        return (_parent ? _parent->getAbsolutePosition2D() : glm::vec2(0)) + _pos2D;
    }

    glm::vec3 Transform::getAbsolutePosition() const {
        return (_parent ? _parent->getAbsolutePosition() : glm::vec3(0)) + _pos3D;
    }


    float& Transform::x() {
        setRelativeMatDirty(true);
        return _pos3D.x;
    }

    float& Transform::y() {
        setRelativeMatDirty(true);
        return _pos3D.y;
    }

    float& Transform::z() {
        setRelativeMatDirty(true);
        return _pos3D.z;
    }

    glm::vec2& Transform::position2D() {
        setRelativeMatDirty(true);
        return _pos2D;
    }

    glm::vec3& Transform::position() {
        setRelativeMatDirty(true);
        return _pos3D;
    }


    // Rotation
    float Transform::getRotation2D() const {
        return _rotation.z;
    }

    glm::vec3 Transform::getRotation() const {
        return _rotation;
    }

    float Transform::getAbsoluteRotation2D() const {
        return (_parent ? _parent->getAbsoluteRotation2D() : 0) + _rotation.z;
    }

    glm::vec3 Transform::getAbsoluteRotation() const {
        return (_parent ? _parent->getAbsoluteRotation() : glm::vec3(0)) + _rotation;
    }


    float& Transform::rotation2D() {
        setRelativeMatDirty(true);
        return _rotation.z;
    }

    glm::vec3& Transform::rotation() {
        setRelativeMatDirty(true);
        return _rotation;
    }


    // Scale
    float Transform::getScaleX() const {
        return _scale3D.x;
    }

    float Transform::getScaleY() const {
        return _scale3D.y;
    }

    float Transform::getScaleZ() const {
        return _scale3D.z;
    }

    glm::vec2 Transform::getScale2D() const {
        return _scale2D;
    }

    glm::vec3 Transform::getScale() const {
        return _scale3D;
    }

    float Transform::getAbsoluteScaleX() const {
        return (_parent ? _parent->getAbsoluteScaleX() : 1) * _scale3D.x;
    }

    float Transform::getAbsoluteScaleY() const {
        return (_parent ? _parent->getAbsoluteScaleY() : 1) * _scale3D.y;
    }

    float Transform::getAbsoluteScaleZ() const {
        return (_parent ? _parent->getAbsoluteScaleZ() : 1) * _scale3D.z;
    }

    glm::vec2 Transform::getAbsoluteScale2D() const {
        return (_parent ? _parent->getAbsoluteScale2D() : glm::vec2(1, 1)) * _scale2D;
    }

    glm::vec3 Transform::getAbsoluteScale() const {
        return (_parent ? _parent->getAbsoluteScale() : glm::vec3(1, 1, 1)) * _scale3D;
    }


    void Transform::setScaleX(float x) {
        setScale(glm::vec3(x, _scale3D.y, _scale3D.z));
    }

    void Transform::setScaleY(float y) {
        setScale(glm::vec3(_scale3D.x, y, _scale3D.z));
    }

    void Transform::setScaleZ(float z) {
        setScale(glm::vec3(_scale3D.x, _scale3D.y, z));
    }

    void Transform::setScale(float x, float y) {
        setScale(glm::vec3(x, y, _scale3D.z));
    }

    void Transform::setScale(const glm::vec2& scale) {
        setScale(glm::vec3(scale, _scale3D.z));
    }

    void Transform::setScale(float x, float y, float z) {
        setScale(glm::vec3(x, y, z));
    }

    void Transform::setScale(const glm::vec3& scale) {
        glm::vec3 oldScale = _scale3D;
        _scale3D = scale;
        setRelativeMatDirty(true);

        if (entity) {
            ScaleChangedEvent e(entity, oldScale, _scale3D);
            entity->getEventService().fire(e);
        }
    }


    // Mat
    const glm::mat4& Transform::toRelativeMatrix() {
        if (_relativeMatDirty) {
            double sx = sin(_rotation.x);
            double cx = cos(_rotation.x);
            double sy = sin(_rotation.y);
            double cy = cos(_rotation.y);
            double sz = sin(_rotation.z);
            double cz = cos(_rotation.z);

            _relativeTransform[0][0] = static_cast<float>(_scale3D.x * (cy * cz));
            _relativeTransform[0][1] = static_cast<float>(_scale3D.x * (cx * sz + sx * sy * cz));
            _relativeTransform[0][2] = static_cast<float>(_scale3D.x * (sx * sz - sy * cx * cz));
            _relativeTransform[0][3] = 0;

            _relativeTransform[1][0] = static_cast<float>(_scale3D.y * (-sz * cy));
            _relativeTransform[1][1] = static_cast<float>(_scale3D.y * (cx * cz - sx * sy * sz));
            _relativeTransform[1][2] = static_cast<float>(_scale3D.y * (sx * cz + sy * sz * cx));
            _relativeTransform[1][3] = 0;

            _relativeTransform[2][0] = static_cast<float>(_scale3D.z * sy);
            _relativeTransform[2][1] = static_cast<float>(_scale3D.z * (-sx * cy));
            _relativeTransform[2][2] = static_cast<float>(_scale3D.z * (cx * cy));
            _relativeTransform[2][3] = 0;

            _relativeTransform[3][0] = _pos3D.x;
            _relativeTransform[3][1] = _pos3D.y;
            _relativeTransform[3][2] = _pos3D.z;
            _relativeTransform[3][3] = 1;

            setRelativeMatDirty(false);
        }

        return _relativeTransform;
    }

    const glm::mat4& Transform::toWorldMatrix() {
        if (_worldMatDirty) {
            const glm::mat4 &relativeMat = toRelativeMatrix();

            if (_parent)
                _worldTransform = _parent->toWorldMatrix() * relativeMat;
            else
                _worldTransform = relativeMat;

            setWorldMatDirty(false);
        }

        return _worldTransform;
    }
};