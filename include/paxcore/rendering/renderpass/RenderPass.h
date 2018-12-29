//
// Created by paul on 29.12.18.
//

#ifndef PAXENGINE3_RENDERPASS_H
#define PAXENGINE3_RENDERPASS_H

#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    template<typename ChildType>
    class RenderPass : public TypedSceneGraph<ChildType> {

    };
}

#endif //PAXENGINE3_RENDERPASS_H
