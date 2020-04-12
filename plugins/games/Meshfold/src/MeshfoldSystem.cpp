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

        Meshfold * meshfold = options.activeWorld->get<Meshfold>();

        if (!meshfold) return;

        for (PointCloudSprite * p : sprites) {
            KeyboardControls * controls = p->getOwner()->get<KeyboardControls>();
            Transformation & t = p->getOwner()->getTransformation();

            float velocity = 0;
            if (controls) {
                float rot = t.getRotation2DInRadians();
                rot += p->dir * controls->angularVelocity * options.dt;
                velocity += controls->velocity * options.dt;
                t.setRotation2DInRadians(rot);
            }

            if (velocity != 0) {
                Meshfold::Transition r = meshfold->traceRay(t.position2D(), p->dir * velocity * t.getRotation2DAsDirection());
                t.position2D() = r.position;
                p->dir *= float(r.flip);
                p->scale *= r.scale;
                t.setRotation2D(p->dir * float(Math::sign(velocity))*r.direction);
            }

            const float rot = t.getRotation2DInRadians();
            glm::mat2 pointTrafo;
            float s = sin(rot);
            float c = cos(rot);
            pointTrafo[0][0] = c;
            pointTrafo[0][1] = s;
            pointTrafo[1][0] = -s;
            pointTrafo[1][1] = c;

            pointTrafo = pointTrafo * glm::mat2(glm::vec2(p->dir, 0), glm::vec2(0, 1));

            for (int i = 0; i < p->positions.size(); ++i) {
                const glm::vec2 dir = pointTrafo * p->scale * p->originalpositions[i];
                /*
                // This is some not-working try to fix the curvature when traversing portals of different size
                float scale = 1.f;
                Meshfold::Transition transition = meshfold->traceRay(t.position2D(), glm::vec2(dir.x, 0.f));
                scale *= transition.scale;

                glm::vec2 nextDir = -dir.y * Math::signPositiveNull(dir.x) * glm::vec2(transition.direction.y, -transition.direction.x);
                glm::vec2 lastPathAfterPortal = transition.distanceTraveledAfterPortal * transition.direction * dir.x;
                transition = meshfold->traceRay(transition.position
                        - lastPathAfterPortal + transition.scale * lastPathAfterPortal
                        , nextDir);
                scale *= transition.scale;
                lastPathAfterPortal = transition.distanceTraveledAfterPortal * transition.direction * dir.y;

                // we have to scale the angle but I dont know how
                p->positions[i] = transition.position +
                                  - lastPathAfterPortal + transition.scale * lastPathAfterPortal;
                                  /*/
                Meshfold::Transition transition = meshfold->traceRay(t.position2D(), dir);
                                  //*/
                p->positions[i] = transition.position + (transition.scale - 1) * transition.distanceTraveledAfterPortal * glm::length(dir) *  transition.direction;
                p->pointsizes[i] = p->pointSize * p->scale * transition.scale;
            }

            p->meshNode.getMesh()->updateAttribute(Mesh::Vertices, p->positions);
            p->meshNode.getMesh()->updateAttribute(PointCloudSprite::PointSizes, p->pointsizes);
        }
    }
}