//
// Created by Paul on 13.08.2018.
//

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxutil/resources/JsonResourceFieldWriter.h>
#include <paxphysics/2d/box2d/Box2DPhysicsSystem.h>
#include <paxphysics/2d/gravityfields/SphereGravityField.h>

#include "paxphysics/Plugin.h"
#include "paxphysics/2d/Hitbox2D.h"
#include "paxphysics/2d/RigidBody2D.h"
#include "paxphysics/2d/PhysicsWorld2D.h"
#include "paxphysics/2d/box2d/Box2DRigidBody.h"
#include "paxphysics/2d/box2d/Box2DHitbox.h"
#include "paxphysics/2d/box2d/Box2DWorld.h"

// Do not remove. This is necessary such that the compiler finds the specialization of the parser.
#include "paxphysics/2d/json/JsonShape2DParser.h"

namespace PAX::Physics {
    void Plugin::registerProperties() {
        //PAX_PROPERTY_REGISTER(PAX::Physics::RigidBody2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DRigidBody, "PAX::Physics::RigidBody2D");

        //PAX_PROPERTY_REGISTER(PAX::Physics::Hitbox2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DHitbox, "PAX::Physics::Hitbox2D");
        
        //PAX_PROPERTY_REGISTER(PAX::Physics::PhysicsWorld2D)
        PAX_PROPERTY_REGISTER_AS(PAX::Physics::Box2DWorld, "PAX::Physics::PhysicsWorld2D");

        PAX_PROPERTY_REGISTER(GravityField);
        PAX_PROPERTY_REGISTER(SphereGravityField);
    }

    void Plugin::registerSystems(PAX::Game &game) {
        auto box2d_pixelsPerMeter = Services::GetGlobalSettings().getOrDefault<float>("physics2d_pixels_per_meter", 1);
        game.addSystem(std::make_unique<Box2DPhysicsSystem>(box2d_pixelsPerMeter));
    }

    void Plugin::registerJsonWriters(Json::JsonFieldWriterRegister &writerRegister) {
        using namespace Json;

        static JsonFieldWriter<Shape2D*> shape2dWriter;
        writerRegister.registerWriter(paxtypeid(Shape2D*), &shape2dWriter);

        static JsonResourceFieldWriter<PhysicsMaterial> materialWriter;
        materialWriter.registerAt(writerRegister);
    }

    void Plugin::registerResourceLoaders(Resources & resources) {
        resources.registerLoader<PhysicsMaterial>(&psxmatLoader);
    }

    void Plugin::postInitialize(PAX::Engine &engine) {

    }
}