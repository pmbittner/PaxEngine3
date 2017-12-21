//
// Created by Paul on 01.05.2017.
//

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
    float Transform::getX() {
        return _pos3D.x;
    }

    float Transform::getY() {
        return _pos3D.y;
    }

    float Transform::getZ() {
        return _pos3D.z;
    }

    glm::vec2 Transform::getPosition2D() {
       return _pos2D;
    }

    glm::vec3 Transform::getPosition() {
        return _pos3D;
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
    float Transform::getRotation2D() {
        return _rotation.z;
    }

    glm::vec3 Transform::getRotation() {
        return _rotation;
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
    float Transform::getScaleX() {
        return _scale3D.x;
    }

    float Transform::getScaleY() {
        return _scale3D.y;
    }

    float Transform::getScaleZ() {
        return _scale3D.z;
    }

    glm::vec2 Transform::getScale2D() {
        return _scale2D;
    }

    glm::vec3 Transform::getScale() {
        return _scale3D;
    }

    float& Transform::scaleX() {
        setRelativeMatDirty(true);
        return _scale3D.x;
    }

    float& Transform::scaleY() {
        setRelativeMatDirty(true);
        return _scale3D.y;
    }

    float& Transform::scaleZ() {
        setRelativeMatDirty(true);
        return _scale3D.z;
    }

    glm::vec2& Transform::scale2D() {
        setRelativeMatDirty(true);
        return _scale2D;
    }

    glm::vec3& Transform::scale() {
        setRelativeMatDirty(true);
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