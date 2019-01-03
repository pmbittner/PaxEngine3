//
// Created by Paul on 05.10.2017.
//

#ifndef PAXENGINE3_GROUPBYSHADERSSCENEGRAPHGENERATOR_H
#define PAXENGINE3_GROUPBYSHADERSSCENEGRAPHGENERATOR_H

#include <paxcore/rendering/scenegraph/nodes/ShadingNode.h>
#include <paxcore/rendering/scenegraph/SceneGraphGenerator.h>

namespace PAX {
    /**
     * This is the default SceneGraphGenerator for 3D scenes.
     * It groups the graphics objects in the scene by their shaders and sorts them
     * by their z position to fasten rendering. Therefore it will built the following structure:
     *
     *                    Root
     *                      |
     *         _____________|______________
     *        |            |               |
     *   ShaderNode1  ShaderNode2 ... ShaderNodeN
     *        |            |               |
     *    Graphics     Graphics        Graphics
     */
    class GroupByShadersSceneGraphGenerator : public SceneGraphGenerator {
        std::unordered_map<Shader*, ShadingNode> _shadersToNodes;

        void onShaderChanged(GraphicsShaderChangedEvent& e);

        void registerGraphics(Graphics *graphics);
        void unregisterGraphicsFromShader(Graphics *graphics, Shader* shader);

    public:
        GroupByShadersSceneGraphGenerator();
        virtual ~GroupByShadersSceneGraphGenerator();

        virtual void addGraphics(const std::shared_ptr<Graphics> & g) override;
        virtual void removeGraphics(const std::shared_ptr<Graphics> & g) override;
    };
}

#endif //PAXENGINE3_GROUPBYSHADERSSCENEGRAPHGENERATOR_H
