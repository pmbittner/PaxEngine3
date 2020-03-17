//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLDEFAULTWORLDSCENEGRAPH_H
#define PAXENGINE3_OPENGLDEFAULTWORLDSCENEGRAPH_H

#include <paxcore/world/scenegraph/WorldSceneGraph.h>

namespace PAX {
    namespace OpenGL{
        class OpenGLDefaultWorldSceneGraph : public WorldSceneGraph {
        public:
            OpenGLDefaultWorldSceneGraph();
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLDEFAULTWORLDSCENEGRAPH_H
