//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_RENDERFACTORY_H
#define PAXENGINE3_RENDERFACTORY_H

namespace PAX {
    class SceneGraph;

    class RenderFactory {
    public:
        virtual SceneGraph* createWorldLayerSceneGraphNode() = 0;
    };
}

#endif //PAXENGINE3_RENDERFACTORY_H
