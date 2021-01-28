//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/2d/Hitbox2D.h>
#include <paxcore/world/World.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxphysics/2d/visualization/HitboxGraphics.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Hitbox2D)

    ClassMetadata Hitbox2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(fixture));
        return m;
    }

    Hitbox2D::~Hitbox2D() {
        pax_delete(visualizer);
    }

    void Hitbox2D::setFixture(const Fixture2D & fixture) {
        this->fixture = fixture;
    }

    const Fixture2D & Hitbox2D::getFixture() const {
        return fixture;
    }

    void Hitbox2D::show() {
        GameEntity * owner = getOwner();
        if (owner) {
            if (visualizer == nullptr) {
                visualizer = pax_new(GameEntity)();
                visualizer->add(pax_new(HitboxGraphics)(fixture));
                visualizer->getTransformation().z() = HitboxVisualizationZ;
            }

            World * w = owner->getWorld();
            if (w) {
                if (visualizer->getParent() != owner) {
                    visualizer->setParent(owner);
                }
                if (visualizer->getWorld() != w) {
                    w->spawn(visualizer);
                }
            }
        }
    }

    void Hitbox2D::hide() {
        if (World * w = visualizer->getWorld()) {
            w->despawn(visualizer);
        }
        if (visualizer->getParent()) {
            visualizer->setParent(nullptr);
        }
    }
}