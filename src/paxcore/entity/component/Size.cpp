//
// Created by Paul on 03.02.2018.
//

#include <paxcore/entity/component/Size.h>
#include <paxcore/entity/event/SizeChangedEvent.h>

namespace PAX {
    Size::Size(const glm::vec3 &size) {
        setSize(size);
    }

    void Size::attached(Entity *entity) {
        EntityComponent::attached(entity);

        SizeChangedEvent e(entity, glm::vec3(0), this);
        entity->getEventService().fire(e);
    }

    void Size::setSize(const glm::vec3 &size) {
        glm::vec3 oldSize = _size;
        _size = size;

        if (Entity *owner = getOwner()) {
            SizeChangedEvent e(owner, oldSize, this);
            owner->getEventService().fire(e);
        }
    }

    void Size::setSize2D(const glm::vec2 &size) {
        setSize(glm::vec3(size, getDepth()));
    }

    float Size::getWidth() const {
        return (getOwner() ? getOwner()->getTransform().getAbsoluteScaleX() : 1) * _size.x;
    }

    float Size::getHeight() const {
        return (getOwner() ? getOwner()->getTransform().getAbsoluteScaleY() : 1) * _size.y;
    }

    float Size::getDepth() const {
        return (getOwner() ? getOwner()->getTransform().getAbsoluteScaleZ() : 1) * _size.z;
    }

    glm::vec3 Size::getSize() const {
        return (getOwner() ? getOwner()->getTransform().getAbsoluteScale() : glm::vec3(1)) * _size;
    }

    glm::vec2 Size::getSize2D() const {
        return (getOwner() ? getOwner()->getTransform().getAbsoluteScale2D() : glm::vec2(1)) * _size2D;
    }

    glm::vec3 Size::getSizeUnscaled() const {
        return _size;
    }

    FloatBoundingBox3D Size::toBoundingBox() {
        float w = getWidth() / 2.f;
        float h = getHeight() / 2.f;
        float d = getDepth() / 2.f;
        float from[3] = {-w, -h, -d};
        float to[3] = {w, h, d};
        return FloatBoundingBox3D(from, to);
    }

    FloatBoundingBox3D Size::toAbsoluteBoundingBox() {
        FloatBoundingBox3D box = toBoundingBox();
        if (Entity *owner = getOwner()) {
            for (Entity* child : owner->getChildren()) {
                if (Size* s = child->get<Size>()) {
                    FloatBoundingBox3D childBox = s->toAbsoluteBoundingBox();
                    // add childs translation and ignore rotation
                    glm::vec3 pos = child->getTransform().getPosition();
                    childBox.translate(&pos[0]);
                    box += childBox;
                }
            }
        }
        return box;
    }
}