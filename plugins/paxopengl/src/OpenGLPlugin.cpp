//
// Created by paul on 19.05.18.
//

#include <paxcore/rendering/scenegraph/generators/GroupByShadersSceneGraphGenerator.h>
#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>
#include <paxcore/rendering/data/Shader.h>
#include <paxopengl/OpenGLPointCloudSettings.h>
#include <paxcore/rendering/renderpass/RenderPassFactory.h>

#include "paxopengl/OpenGLPlugin.h"
#include "paxopengl/glslpreprocessor/GLSLIncludeDirectives.h"

namespace PAX {
    namespace OpenGL {
        WorldSceneGraph * OpenGLPlugin::OpenGLWorldSceneGraphFactory::create(World *world) {
            return new OpenGLDefaultWorldSceneGraph();
        }

        void OpenGLPlugin::initialize(Engine &engine) {}

        void OpenGLPlugin::postInitialize(Engine &engine) {
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
            factoryService.set(paxtypeid(RenderPassFactory), &renderPassFactory);
        }

        void OpenGLPlugin::registerServices(Services &services) {
            pointCloudSettings.initialize();
            services.registerService(paxtypeid(PointCloudSettings), &pointCloudSettings);

            preprocessorService.addAndOwnPreprocessor(new GLSLIncludeDirectives());
            services.registerService(paxtypeid(GLSLPreprocessorService), &preprocessorService);
        }
    }
}