//
// Created by Paul Bittner on 21.03.2020.
//

#include <meshfold/MeshfoldSystem.h>
#include <meshfold/properties/KeyboardControls.h>
#include <paxutil/math/Functions.h>

namespace PAX {
    void MeshfoldSystem::initialize(PAX::Game * game) {
        GameSystem::initialize(game);
        sprites.initialize();
    }

    void MeshfoldSystem::update(UpdateOptions &options) {
        GameSystem::update(options);

        Meshfold * meshfold = getGame()->getActiveWorld()->get<Meshfold>();

        for (PointCloudSprite * p : sprites) {
            KeyboardControls * controls = p->getOwner()->get<KeyboardControls>();
            Transformation & t = p->getOwner()->getTransformation();

            float velocity = 0;
            if (controls) {
                float rot = t.getRotation2DInRadians();
                rot += controls->angularVelocity * options.dt;
                velocity += controls->velocity * options.dt;
                t.setRotation2DInRadians(rot);
            }

            if (velocity != 0) {
                Meshfold::Ray r = meshfold->traceRay(t.position2D(), velocity * t.getRotation2DAsDirection());
                t.position2D() = r.p;
                t.setRotation2D(Math::sign(velocity)*r.d);
            }

            float rot = t.getRotation2DInRadians();

            glm::mat2 rotationMatrix;
            float s = sin(rot);
            float c = cos(rot);
            rotationMatrix[0][0] = c;
            rotationMatrix[0][1] = s;
            rotationMatrix[1][0] = -s;
            rotationMatrix[1][1] = c;

            for (int i = 0; i < p->positions.size(); ++i) {
                p->positions[i] =
                        /*
                        t.position2D() + rotationMatrix * p->originalpositions[i];
                        /*/
                        meshfold->traceRay(t.position2D(), rotationMatrix * p->originalpositions[i]).p;//*/
            }

            p->meshNode.getMesh()->updateAttribute(Mesh::Vertices, p->positions);
        }
    }
}