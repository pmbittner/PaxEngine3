//
// Created by Paul on 06.01.2018.
//

#include <paxcore/rendering/scenegraph/generators/SortByZSceneGraphGenerator.h>

namespace PAX {
    SortByZSceneGraphGenerator::SortingNode::SortingNode() : TypedSceneGraph<Graphics>() {}

    void SortByZSceneGraphGenerator::SortingNode::render(PAX::RenderOptions &renderOptions) {
        sorter.sort(_children);
        // TODO: Short by shader?

        Shader* currentShader = nullptr;
        bool reassignShader;

        for (Graphics* g : _children) {
            reassignShader = currentShader != g->getShader().get();

            if (reassignShader) {
                if (currentShader)
                    renderOptions.getShaderOptions().popShader(this);

                currentShader = g->getShader().get();
                renderOptions.getShaderOptions().pushShader(this, currentShader, ShaderPriority::MUTABLE);
            }

            g->render(renderOptions);
        }

        if (currentShader)
            renderOptions.getShaderOptions().popShader(this);
    }

    SortByZSceneGraphGenerator::SortByZSceneGraphGenerator() : SceneGraphGenerator() {
        sceneRoot.addChild(&sortingNode);
    }

    SortByZSceneGraphGenerator::~SortByZSceneGraphGenerator() = default;

    void SortByZSceneGraphGenerator::addGraphics(const std::shared_ptr<PAX::Graphics> &g) {
        sortingNode.addChild(g.get());
    }

    void SortByZSceneGraphGenerator::removeGraphics(const std::shared_ptr<PAX::Graphics> &g) {
        sortingNode.removeChild(g.get());
    }
}