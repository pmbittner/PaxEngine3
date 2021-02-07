//
// Created by Paul on 13.08.2018.
//

#ifndef PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H
#define PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "2d/material/PhysicsMaterialLoader.h"
#include "2d/Hitbox2D.h"
#include "2d/RigidBody2D.h"
#include "2d/PhysicsWorld2D.h"

namespace PAX::Physics {
    class Plugin : public EnginePlugin {
        PhysicsMaterialLoader psxmatLoader;

    public:
        static constexpr const char * HITBOX2D = "Hitbox2D";
        static constexpr const char * RIGIDBODY2D = "RigidBody2D";
        static constexpr const char * PHYSICSWORLD2D = "PhysicsWorld2D";

        void registerProperties() override;
        void registerResourceLoaders(Resources & resources) override;
        void registerSystems(Game& game) override;
        void registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) override;
        void postInitialize(Engine & engine) override;

        PAX_NODISCARD static Hitbox2D * CreateHitbox(const std::shared_ptr<Shape2D> & shape,
                                                     const std::shared_ptr<PhysicsMaterial> &material = PhysicsMaterial::GetDefaultMaterial());
        PAX_NODISCARD static RigidBody2D * CreateRigidBody2D();
        PAX_NODISCARD static PhysicsWorld2D * CreatePhysicsWorld2D();
    };
}

#endif //PAXENGINE3_PAXPHYSICSPLUGIN_PLUGIN_H
