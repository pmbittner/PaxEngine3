//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/2d/Hitbox2D.h>
#include <paxcore/world/World.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <polypropylene/log/Assert.h>
#include <paxphysics/2d/visualization/HitboxGraphics.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Hitbox2D)

    ClassMetadata Hitbox2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(fixtures));
        m.add(paxfieldof(fixedRotation));
        return m;
    }

    Hitbox2D::Hitbox2D() = default;
    Hitbox2D::~Hitbox2D() {
        for (GameEntity * visualizer : fixtureVisualizers) {
            pax_delete(visualizer);
        }
    }

    void Hitbox2D::setFixtures(const std::vector<Fixture2D> & fixtures) {
        this->fixtures = fixtures;
        PAX_ASSERT(fixtureVisualizers.empty());
        fixtureVisualizers.reserve(fixtures.size());
    }

    const std::vector<Fixture2D>& Hitbox2D::getFixtures() const {
        return fixtures;
    }

    bool Hitbox2D::hasFixedRotation() const {
        return fixedRotation;
    }

    void Hitbox2D::setFixedRotation(bool fixedRotation) {
        this->fixedRotation = fixedRotation;
    }

    void Hitbox2D::show() {
        GameEntity * owner = getOwner();
        if (owner) {
            if (fixtureVisualizers.empty()) {
                for (Fixture2D & fixture : fixtures) {
                    GameEntity * visualizer = pax_new(GameEntity)();
                    visualizer->add(pax_new(HitboxGraphics)(fixture));
                    visualizer->getTransformation().z() = HitboxVisualizationZ;
                    fixtureVisualizers.push_back(visualizer);
                }
            }

            World * w = owner->getWorld();
            if (w) {
                for (GameEntity * visualizer : fixtureVisualizers) {
                    if (visualizer->getParent() != owner) {
                        visualizer->setParent(owner);
                    }
                    if (visualizer->getWorld() != w) {
                        w->spawn(visualizer);
                    }
                }
            }
        }
    }

    void Hitbox2D::hide() {
        for (GameEntity * visualizer : fixtureVisualizers) {
            if (World * w = visualizer->getWorld()) {
                w->despawn(visualizer);
            }
            if (visualizer->getParent()) {
                visualizer->setParent(nullptr);
            }
        }
    }
}