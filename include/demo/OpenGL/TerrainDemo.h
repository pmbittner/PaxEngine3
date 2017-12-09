//
// Created by Paul on 09.12.2017.
//

#ifndef PAXENGINE3_3DDEMO_H
#define PAXENGINE3_3DDEMO_H

#include <opengl/OpenGLViewport.h>
#include <generation/terrain/TerrainGenerator.h>
#include <core/entity/component/behaviours/NoClipControls.h>
#include <demo/behaviours/RotateAround3D.h>
#include "OpenGLDemo.h"

namespace PAX {
    namespace Demo {
        class TerrainDemo : public OpenGLDemo {
        public:
            TerrainDemo() : OpenGLDemo() {

            }

            ~TerrainDemo() {

            }

            virtual void initialize() override {
                OpenGLDemo::initialize();

                EntityComponentService &componentAllocator = Services::GetEntityComponentService();
                Window* window = Engine::Instance().getWindow();

                World *world = new World();
                glm::ivec2 res = window->getResolution();

                int terrainScale = 5;

                Entity *camera = new Entity();
                camera->add(componentAllocator.create<Camera>(
                        new OpenGL::OpenGLViewport(0, 0, res.x, res.y),
                        new PerspectiveProjection()
                ));
                camera->getTransform().position() = glm::vec3(0, ceil(terrainScale/2.f), 4);
                camera->add<Behaviour>(componentAllocator.create<NoClipControls>());

                Entity *terrainEntity = new Entity();

                TerrainGenerator terrainGenerator;
                Terrain *t = terrainGenerator.generateTerrain();
                Shader *s = Services::GetResources().loadOrGet<Shader>(
                        (Services::GetPaths().RelativeResourcePath() + "shader/terrain/terrain.vert").c_str(),
                        (Services::GetPaths().RelativeResourcePath() + "shader/terrain/terrain.frag").c_str()
                );
                s->cacheUniforms({"modelview", "projection"});
                t->setShader(s);
                terrainEntity->add<Graphics>(t);
                terrainEntity->getTransform().scaleY() = terrainScale;
                //terrainEntity->add<Behaviour>(componentAllocator.create<RotateAround3D>(glm::vec3(0, 0.001f, 0)));
                LOG(INFO) << "RenderTests: Entities initialized";

                world->getMainLayer()->spawn(camera);
                world->getMainLayer()->spawn(terrainEntity);

                setActiveWorld(world);
                Game::initialize();

                LOG(INFO) << "RenderTests: Game initialized";
            }
        };
    }
}
#endif //PAXENGINE3_3DDEMO_H
