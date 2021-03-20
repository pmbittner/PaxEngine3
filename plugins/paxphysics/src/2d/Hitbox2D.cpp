//
// Created by Paul on 22.03.2019.
//

#include <paxphysics/2d/Hitbox2D.h>
#include <paxcore/world/World.h>
#include <paxcore/rendering/graphics/SpriteGraphics.h>
#include <paxphysics/2d/visualization/HitboxGraphics.h>
#include <paxutil/reflection/EngineFieldFlags.h>

namespace PAX::Physics {
    PAX_PROPERTY_IMPL(PAX::Physics::Hitbox2D)

    ClassMetadata Hitbox2D::getMetadata() {
        ClassMetadata m = Super::getMetadata();
        m.add(paxfieldof(shape)).addFlag(Field::IsMandatory);
        m.add(paxfieldof(material)).addFlag(Field::IsMandatory | EngineFieldFlags::IsResource);
        m.add(paxfieldof(isTrigger));
        m.add(paxfieldof(name));
        return m;
    }

    Hitbox2D::Hitbox2D(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material)
    : shape(shape), material(material) {}

    Hitbox2D::~Hitbox2D() {
        pax_delete(visualizer);
    }

    void Hitbox2D::show() {
        GameEntity * owner = getOwner();
        if (owner) {
            GameEntity * visualizer = getVisualizer();
            if (World * w = getWorld()) {
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

    void Hitbox2D::onHitBeginWith(Hitbox2D &hitbox) {
        contacts.push_back(&hitbox);
        OnHitBegin(hitbox);
    }

    void Hitbox2D::onHitEndWith(Hitbox2D &hitbox) {
        OnHitEnd(hitbox);
        Util::removeFromVector(contacts, &hitbox);
    }

    const std::vector<Hitbox2D *> & Hitbox2D::getCurrentContacts() const {
        return contacts;
    }

    void Hitbox2D::setTriggerArea(bool isTrigger) {
        this->isTrigger = isTrigger;
    }

    bool Hitbox2D::isTriggerArea() const {
        return isTrigger;
    }

    const std::shared_ptr<Shape2D> & Hitbox2D::getShape() const {
        return shape;
    }

    const std::shared_ptr<PhysicsMaterial> & Hitbox2D::getMaterial() const {
        return material;
    }

    GameEntity * Hitbox2D::getVisualizer() {
        if (visualizer == nullptr) {
            MotionType m = MotionType::Static;
            if (GameEntity * owner = getOwner()) {
                m = owner->getMotionType();
            }
            visualizer = pax_new(GameEntity)();
            visualizer->i_setMotionType(m);
            visualizer->add(pax_new(HitboxGraphics)(*shape, m));
            visualizer->getTransformation().z() = HitboxVisualizationZ;
        }

        return visualizer;
    }

    HitboxGraphics * Hitbox2D::getVisualisation() {
        return getVisualizer()->get<HitboxGraphics>();
    }

    const std::string &Hitbox2D::getName() const {
        return name;
    }

    void Hitbox2D::setName(const std::string &name) {
        Hitbox2D::name = name;
    }
}