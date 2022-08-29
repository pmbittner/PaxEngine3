//
// Created by Paul on 29.08.2022.
//

#ifndef PAXENGINE3_IMGUIRENDERER_H
#define PAXENGINE3_IMGUIRENDERER_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    namespace Imgui {
        class ImguiPlugin;

        class ImguiRenderer : public SceneGraph {
            const ImguiPlugin & plugin;

        public:
            ImguiRenderer(const ImguiPlugin & plugin);

            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_IMGUIRENDERER_H
