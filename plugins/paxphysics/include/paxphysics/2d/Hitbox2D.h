//
// Created by Paul on 22.03.2019.
//

#ifndef PAXENGINE3_HITBOX2D_H
#define PAXENGINE3_HITBOX2D_H

#include <paxcore/gameentity/GameEntityProperty.h>
#include <paxphysics/2d/shape/Shape2D.h>
#include <paxphysics/2d/material/PhysicsMaterial.h>
#include <paxphysics/2d/visualization/HitboxGraphics.h>

namespace PAX::Physics {
    class Hitbox2D : public GameEntityProperty {
        PAX_PROPERTY(PAX::Physics::Hitbox2D, PAX_PROPERTY_IS_ABSTRACT)
        PAX_PROPERTY_DERIVES(PAX::GameEntityProperty)
        PAX_PROPERTY_IS_MULTIPLE

        friend class PhysicsSystem2D;
        friend class PhysicsWorld2D;

        GameEntity* visualizer = nullptr;
        PAX_NODISCARD GameEntity * getVisualizer();

        /// Begin Fields
        std::string name = "<unknown>";
        std::shared_ptr<Shape2D> shape = nullptr;
        std::shared_ptr<PhysicsMaterial> material;
        bool isTrigger = false;
        /// End Fields

        std::vector<Hitbox2D*> contacts;

        void onHitBeginWith(Hitbox2D & hitbox);
        void onHitEndWith(Hitbox2D & hitbox);

    protected:
        Hitbox2D(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material);

    public:
        static constexpr int HitboxVisualizationZ = 100;
        EventHandler<Hitbox2D&> OnHitBegin;
        EventHandler<Hitbox2D&> OnHitEnd;

        ~Hitbox2D() override = 0;

        PAX_NODISCARD ClassMetadata getMetadata() override;

        void show();
        void hide();

        PAX_NODISCARD virtual bool isInside(const glm::vec2 & point) const = 0;

        /**
         * @param isTrigger Defines if this hitbox will behave as a trigger.
         *                  If set to true, this hitbox will never be solid, even if
         *                  paired with a RigidBody2D.
         *                  If set to false, this hitbox will be solid when attached to
         *                  an entity with a RigidBody2D.
         *                  Default value is `false`.
         */
        virtual void setTriggerArea(bool isTrigger);
        PAX_NODISCARD bool isTriggerArea() const;
        PAX_NODISCARD const std::shared_ptr<Shape2D> & getShape() const;
        PAX_NODISCARD const std::shared_ptr<PhysicsMaterial> & getMaterial() const;
        PAX_NODISCARD HitboxGraphics * getVisualisation();
        PAX_NODISCARD const std::vector<Hitbox2D*> & getCurrentContacts() const;
        PAX_NODISCARD const std::string &getName() const;
        void setName(const std::string &name);
    };
}

#endif //PAXENGINE3_HITBOX2D_H
