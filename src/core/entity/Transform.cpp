//
// Created by Paul on 01.05.2017.
//

#include "../../../include/core/entity/Transform.h"
#include "../../../include/utility/stdutils.h"

namespace PAX {
    Transform::Transform() :
            _pos3D(0), _rotation(0), _scale3D(1),
            _parent(nullptr),
            _relativeMatDirty(true), _worldMatDirty(true)
    {

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
                Util::removeFromVector(&(_parent->_children), this);

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
    void Transform::setX(float x) {
        _pos3D.x = x;
        setRelativeMatDirty(true);
    }

    void Transform::setY(float y) {
        _pos3D.y = y;
        setRelativeMatDirty(true);
    }

    void Transform::setZ(float z) {
        _pos3D.z = z;
        setRelativeMatDirty(true);
    }

    void Transform::setPosition(float x, float y) {
        _pos2D = {x, y};
        setRelativeMatDirty(true);
    }

    void Transform::setPosition(float x, float y, float z) {
        _pos3D = {x, y, z};
        setRelativeMatDirty(true);
    }

    void Transform::setPosition(glm::vec2 pos) {
        _pos2D = pos;
        setRelativeMatDirty(true);
    }

    void Transform::setPosition(glm::vec3 pos) {
        _pos3D = pos;
        setRelativeMatDirty(true);
    }


    float Transform::x() {
        return _pos3D.x;
    }

    float Transform::y() {
        return _pos3D.y;
    }

    float Transform::z() {
        return _pos3D.z;
    }

    glm::vec2 Transform::xy() {
        return _pos2D;
    }

    glm::vec3 Transform::xyz() {
        return _pos3D;
    }


    // Rotation
    void Transform::setRotation(float rotation) {
        _rotation.z = rotation;
        setRelativeMatDirty(true);
    }

    void Transform::setRotation(float x, float y, float z) {
        _rotation = {x, y, z};
        setRelativeMatDirty(true);
    }

    void Transform::setRotation(glm::vec3 rotation) {
        _rotation = rotation;
        setRelativeMatDirty(true);
    }


    float Transform::getRotation() {
        return _rotation.z;
    }

    glm::vec3 Transform::getRotation3D() {
        return _rotation;
    }


    // Scale
    void Transform::setScaleX(float x) {
        _scale3D.x = x;
        setRelativeMatDirty(true);
    }

    void Transform::setScaleY(float y) {
        _scale3D.y = y;
        setRelativeMatDirty(true);
    }

    void Transform::setScaleZ(float z) {
        _scale3D.z = z;
        setRelativeMatDirty(true);
    }

    void Transform::setScale(float x, float y) {
        _scale2D = {x, y};
        setRelativeMatDirty(true);
    }

    void Transform::setScale(float x, float y, float z) {
        _scale3D = {x, y, z};
        setRelativeMatDirty(true);
    }

    void Transform::setScale(glm::vec3 scale) {
        _scale3D = scale;
        setRelativeMatDirty(true);
    }


    float Transform::getScaleX() {
        return _scale3D.x;
    }

    float Transform::getScaleY() {
        return _scale3D.y;
    }

    float Transform::getScaleZ() {
        return _scale3D.z;
    }

    glm::vec2 Transform::getScale() {
        return _scale2D;
    }

    glm::vec3 Transform::getScale3D() {
        return _scale3D;
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