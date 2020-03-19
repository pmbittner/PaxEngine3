//
// Created by paul on 19.05.18.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>
#include <paxcore/rendering/data/Shader.h>

#include "paxopengl/OpenGLPlugin.h"

namespace PAX {
    namespace OpenGL {
        WorldSceneGraph * OpenGLPlugin::OpenGLWorldSceneGraphFactory::create(World *world) {
            return new OpenGLDefaultWorldSceneGraph();
        }

        void OpenGLPlugin::initialize(Engine &engine) {}

        void OpenGLPlugin::postInitialize(Engine &engine) {
            glEnable(GL_PROGRAM_POINT_SIZE);
            glPointSize(3);
        }

        void OpenGLPlugin::registerResourceLoaders(Resources &resources) {
            resources.registerLoader<Shader>(static_cast<ResourceLoader<Shader, Shader::FileInfo> *>(&shaderLoader));
        }

        void OpenGLPlugin::registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) {
            shaderJsonParser.registerAt(writerRegister);
        }

        void OpenGLPlugin::registerFactories(FactoryService &factoryService) {
            factoryService.set(paxtypeid(MeshFactory), &meshFactory);
            factoryService.set(paxtypeid(ViewportFactory), &viewportFactory);
            factoryService.set(paxtypeid(WorldSceneGraphFactory), &worldSceneGraphFactory);
            factoryService.set(paxtypeid(TextureFactory), &textureFactory);
        }
    }
}