//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLSPRITE_H
#define PAXENGINE3_OPENGLSPRITE_H

#include <GL/glew.h>
#include <opengl/rendernodes/OpenGLTexturingNode.h>
#include <opengl/rendernodes/OpenGLMeshNode.h>
#include <core/rendering/SceneGraphGraphics.h>
#include <core/rendering/scenegraph/nodes/TransformationNode.h>
#include <core/rendering/resource/SpriteSheet.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLMesh;
        class OpenGLShader;

        class OpenGLSprite : public SceneGraphGraphics {
            static OpenGLMesh *QuadMesh;
            static OpenGLMesh *GetMesh();

            TransformationNode _trafoNode;
            OpenGLTexturingNode _textureNode;
            OpenGLMeshNode _meshNode;

        public:
            OpenGLSprite(const std::shared_ptr<Texture> &texture);
        };
    }
}

#endif //PAXENGINE3_OPENGLSPRITE_H
