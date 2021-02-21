//
// Created by Paul Bittner on 23.01.2021.
//

#include <paxphysics/2d/gravityfields/GravityField.h>
#include <paxphysics/Plugin.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(GravityField)

    const Tag & GravityField::GetTag() {
        static Tag t = "GravityField";
        return t;
    }

    const glm::vec4 & GravityField::GetDefaultVisualizerFillColor() {
        static auto c = glm::vec4(1, 1, 1, 0.4f);
        return c;
    }

    const glm::vec4 & GravityField::GetDefaultVisualizerBorderColor() {
        static auto c = glm::vec4(1);
        return c;
    }

    GravityField::GravityField() = default;

    GravityField::GravityField(const std::shared_ptr<Shape2D> & shape, float intensity)
    : intensity(intensity), hitbox(Plugin::CreateHitbox(shape))
    {
        initializeHitbox();
    }

    GravityField::~GravityField() {
        if (!getOwner()) {
            pax_delete(hitbox);
        }
    }

    void GravityField::initializeHitbox() {
        hitbox = Plugin::CreateHitbox(shape);
        hitbox->setTriggerArea(true);
        HitboxGraphics * g = hitbox->getVisualisation();
        g->setBorderColor(GetDefaultVisualizerBorderColor());
        g->setFillColor(GetDefaultVisualizerFillColor());
    }

    ClassMetadata GravityField::getMetadata() {
        ClassMetadata c = Super::getMetadata();
        c.add(paxfieldof(shape)).addFlag(Field::IsMandatory);
        c.add(paxfieldof(intensity)).addFlag(Field::IsMandatory);
        c.add(paxfieldof(priority));
        return c;
    }

    void GravityField::created() {
        Super::created();
        initializeHitbox();
    }

    void GravityField::attached(GameEntity &entity) {
        Super::attached(entity);
        entity.add(hitbox);
        entity.addTag(GetTag());
    }

    void GravityField::detached(GameEntity &entity) {
        entity.removeTag(GetTag());
        entity.remove(hitbox);
        Super::detached(entity);
    }

    void GravityField::setIntensity(float intensity) {
        this->intensity = intensity;
    }

    float GravityField::getIntensity() const {
        return intensity;
    }

    void GravityField::setPriority(float newPriority) {
        const float oldPriority = priority;
        priority = newPriority;
        OnPriorityChanged(*this, oldPriority, newPriority);
    }

    float GravityField::getPriority() const {
        return priority;
    }

    bool GravityField::isInside(const glm::vec2 &point) const {
        return hitbox->isInside(point);
    }
}
