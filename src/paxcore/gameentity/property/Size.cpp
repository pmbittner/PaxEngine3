//
// Created by Paul on 03.02.2018.
//

#include <paxcore/gameentity/property/Size.h>
#include <paxcore/gameentity/event/SizeChangedEvent.h>

namespace PAX {
    PAX_PROPERTY_IMPL(PAX::Size)

    ClassMetadata Size::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(size)).flags = Field::IsMandatory;
        return m;
    }

    Size::Size(const glm::vec3 & size) : size(size) {
        // size2D is initialised implicitly because it is inside a union with this->size
    }

    void Size::attached(GameEntity &entity) {
        Super::attached(entity);
        SizeChangedEvent e(&entity, glm::vec3(0), this);
        entity.getEventService().fire(e);
    }

    void Size::setSize(const glm::vec3 &size) {
        glm::vec3 oldSize = this->size;
        this->size = size;

        if (GameEntity *owner = getOwner()) {
            SizeChangedEvent e(owner, oldSize, this);
            owner->getEventService().fire(e);
        }
    }

    void Size::setSize2D(const glm::vec2 &size) {
        setSize(glm::vec3(size, getDepth()));
    }

    float Size::getWidth() const {
        return (getOwner() ? getOwner()->getTransformation().getAbsoluteScale().x : 1) * size.x;
    }

    float Size::getHeight() const {
        return (getOwner() ? getOwner()->getTransformation().getAbsoluteScale().y : 1) * size.y;
    }

    float Size::getDepth() const {
        return (getOwner() ? getOwner()->getTransformation().getAbsoluteScale().z : 1) * size.z;
    }

    glm::vec3 Size::getSize() const {
        return (getOwner() ? getOwner()->getTransformation().getAbsoluteScale() : glm::vec3(1)) * size;
    }

    glm::vec2 Size::getSize2D() const {
        return (getOwner() ? glm::vec2(getOwner()->getTransformation().getAbsoluteScale()) : glm::vec2(1)) * size2D;
    }

    glm::vec3 Size::getSizeUnscaled() const {
        return size;
    }

    FloatBoundingBox3D Size::toBoundingBox() const {
        glm::vec3 halfSize = getSize() / 2.f;
        return FloatBoundingBox3D(-halfSize, +halfSize);
    }

    FloatBoundingBox3D Size::toAbsoluteBoundingBox() const {
        FloatBoundingBox3D box = toBoundingBox();

        if (GameEntity *owner = getOwner()) {
            for (GameEntity* child : owner->getChildren()) {
                if (Size * s = child->get<Size>()) {
                    FloatBoundingBox3D childBox = s->toAbsoluteBoundingBox();
                    // add childs translation and ignore rotation
                    glm::vec3 pos = child->getTransformation().position();
                    childBox.translate(pos);
                    box += childBox;
                }
            }
        }

        return box;
    }
}