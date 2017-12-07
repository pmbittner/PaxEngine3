//
// Created by Paul on 02.07.2017.
//

#ifndef PAXENGINE3_OPENGLSPRITE_H
#define PAXENGINE3_OPENGLSPRITE_H

#include <GL/glew.h>
#include <core/rendering/Graphics.h>
#include <opengl/rendernodes/OpenGLTexturingNode.h>
#include <opengl/rendernodes/OpenGLMeshNode.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLMesh;
        class OpenGLShader;

        class OpenGLSprite : public Graphics {
            static OpenGLMesh *QuadMesh;
            static OpenGLMesh *GetMesh();

            OpenGLTexturingNode _textureNode;
            OpenGLMeshNode _meshNode;

        public:
            OpenGLSprite(Texture *texture);
        };
    }
}

#endif //PAXENGINE3_OPENGLSPRITE_H
