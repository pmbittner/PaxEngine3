//
// Created by Paul on 07.12.2017.
//

#ifndef PAXENGINE3_OPENGLMESHNODE_H
#define PAXENGINE3_OPENGLMESHNODE_H

#include <core/rendering/scenegraph/nodes/MeshNode.h>
#include <opengl/resource/OpenGLMesh.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLMeshNode : public MeshNode {
        public:
            OpenGLMeshNode(OpenGLMesh *mesh);
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLMESHNODE_H
