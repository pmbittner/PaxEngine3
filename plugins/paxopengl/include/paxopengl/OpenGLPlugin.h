//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_OPENGLPLUGIN_H
#define PAXENGINE3_OPENGLPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/service/Services.h>
#include <paxcore/world/scenegraph/WorldSceneGraph.h>
#include <paxcore/world/scenegraph/WorldSceneGraphFactory.h>
#include <paxcore/rendering/scenegraph/generators/SceneGraphGeneratorFactory.h>
#include <paxopengl/factory/OpenGLTextureFactory.h>
#include <paxutil/resources/JsonResourceFieldWriter.h>

#include "factory/OpenGLMeshFactory.h"
#include "factory/OpenGLViewportFactory.h"
#include "factory/OpenGLRenderPassFactory.h"
#include "paxopengl/rendernodes/OpenGLDefaultWorldSceneGraph.h"
#include "io/OpenGLShaderLoader.h"

#include "OpenGLPointCloudSettings.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLPlugin : public EnginePlugin {
            class OpenGLWorldSceneGraphFactory : public WorldSceneGraphFactory {
                WorldSceneGraph * create(World *world) override;
            } worldSceneGraphFactory;

            OpenGLShaderLoader shaderLoader;
            OpenGLMeshFactory meshFactory;
            OpenGLViewportFactory viewportFactory;
            OpenGLTextureFactory textureFactory;
            OpenGLRenderPassFactory renderPassFactory;
            OpenGLPointCloudSettings pointCloudSettings;

            JsonResourceFieldWriter<Shader> shaderJsonParser;

        public:
            void initialize(Engine& engine) override;
            void postInitialize(Engine& engine) override;
            void registerResourceLoaders(Resources& resources) override;
            void registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) override;
            void registerFactories(FactoryService& factoryService) override;
            void registerServices(Services & services) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLPLUGIN_H
