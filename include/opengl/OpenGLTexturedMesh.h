//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLTEXTUREDMESH_H
#define PAXENGINE3_OPENGLTEXTUREDMESH_H

#include "core/rendering/TexturedMesh.h"
#include "resource/OpenGLTexture2D.h"
#include "resource/OpenGLMesh.h"
#include "resource/OpenGLShader.h"

namespace PAX {
    namespace OpenGL {
        class OpenGLTexturedMesh : public TexturedMesh {
        public:
            glm::vec3 _color;
            OpenGLTexturedMesh(OpenGLTexture2D *texture, OpenGLMesh *mesh);
            virtual void render(RenderOptions &renderOptions) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLTEXTUREDMESH_H
