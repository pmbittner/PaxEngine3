//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxutil/resources/JsonResourceFieldWriter.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>
#include <paxphysics/2d/gravityfields/GravityFieldSystem.h>
#include <paxphysics/2d/gravityfields/GravityFieldRegister.h>

#include "paxphysics/Plugin.h"
#include "paxphysics/2d/box2d/Box2DWorld.h"
#include "paxphysics/2d/gravityfields/SphereGravityField.h"
#include "paxphysics/2d/gravityfields/DirectionalGravityField.h"
#include "paxphysics/2d/gravityfields/GravityFieldSensitive.h"

// Do not remove. This is necessary such that the compiler finds the specialization of the parser.
#include "paxphysics/2d/json/JsonShape2DParser.h"

namespace PAX::Physics {
    void Plugin::registerProperties() {
        //PAX_PROPERTY_REGISTER(PAX::Physics::RigidBody2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DRigidBody, RIGIDBODY2D);

        //PAX_PROPERTY_REGISTER(PAX::Physics::Hitbox2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DHitbox, HITBOX2D);
        
        //PAX_PROPERTY_REGISTER(PAX::Physics::PhysicsWorld2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DWorld, PHYSICSWORLD2D);

        PAX_PROPERTY_REGISTER(SphereGravityField);
        PAX_PROPERTY_REGISTER(DirectionalGravityField);
        PAX_PROPERTY_REGISTER(GravityFieldSensitive);
        PAX_PROPERTY_REGISTER(GravityFieldRegister);
    }

    void Plugin::registerSystems(PAX::Game &game) {
        game.addSystem(std::make_unique<Box2DPhysicsSystem>());
        game.addSystem(std::make_unique<GravityFieldSystem>());
    }

    void Plugin::registerJsonWriters(Json::JsonFieldWriterRegister &writerRegister) {
        using namespace Json;

        static JsonFieldWriter<std::shared_ptr<Shape2D>> shape2dWriter;
        writerRegister.registerWriter(paxtypeid(std::shared_ptr<Shape2D>), &shape2dWriter);

        static JsonResourceFieldWriter<PhysicsMaterial> materialWriter;
        materialWriter.registerAt(writerRegister);
    }

    void Plugin::registerResourceLoaders(Resources & resources) {
        resources.registerLoader<PhysicsMaterial>(&psxmatLoader);
    }

    void Plugin::postInitialize(PAX::Engine &engine) {

    }

    static GameEntityProperty * CreateProp(const char* name) {
        IPropertyFactory<GameEntity> * f =
                PropertyFactoryRegister<GameEntity>::getFactoryFor(name);
        if (f) {
            GameEntityProperty * p = f->create();
            if (p) {
                return p;
            } else {
                PAX_THROW_RUNTIME_ERROR("Could not create " << name << "!");
            }
        } else {
            PAX_THROW_RUNTIME_ERROR("There is no IPropertyFactory registered for type \"" << name << "\"!");
        }
    }

    Hitbox2D * Plugin::CreateHitbox(const std::shared_ptr<Shape2D> & shape, const std::shared_ptr<PhysicsMaterial> &material) {
        return pax_new(Box2DHitbox)(shape, material);
    }

    RigidBody2D * Plugin::CreateRigidBody2D() {
        if (auto * r = dynamic_cast<RigidBody2D*>(CreateProp(RIGIDBODY2D))) {
            return r;
        }
        PAX_THROW_RUNTIME_ERROR("Could not cast property created by IPropertyFactory registered for "
                                        << RIGIDBODY2D << " to RigidBody2D.");
    }

    PhysicsWorld2D * Plugin::CreatePhysicsWorld2D() {
        if (auto * w = dynamic_cast<PhysicsWorld2D*>(CreateProp(PHYSICSWORLD2D))) {
            return w;
        }
        PAX_THROW_RUNTIME_ERROR("Could not cast property created by IPropertyFactory registered for "
                                        << PHYSICSWORLD2D << " to PhysicsWorld2D.");
    }
}