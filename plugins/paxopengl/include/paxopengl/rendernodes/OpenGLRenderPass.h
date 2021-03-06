//
// Created by Bittner on 08.04.2019.
//

#ifndef PAXENGINE3_OPENGLRENDERPASS_H
#define PAXENGINE3_OPENGLRENDERPASS_H

#include <paxcore/rendering/renderpass/RenderPass.h>
#include <GL/glew.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLRenderPass : public RenderPass {
            GLuint fbo;
            GLuint depth_rb;

            std::map<std::string, GLenum> attachmentOfRenderPass;

        public:
            struct RenderPassBind {
                struct Passes {
                    GLuint drawBuffer;
                    GLuint readBuffer;

                    Passes(GLuint drawBuffer, GLuint readBuffer = 0);
                };

                void push(Passes p);
                void pop();

            private:
                std::stack<Passes> frameBuffers;
                void bindTop();
            };

            static RenderPassBind RenderPassBinder;

            OpenGLRenderPass(const glm::ivec2 & resolution);
            ~OpenGLRenderPass() override;

            void finalize() override;

            void render(RenderOptions &renderOptions) override;
            PAX_NODISCARD std::shared_ptr<Image> getPixelsOfChannel(const std::string & channelName, const glm::ivec2 & upperLeft, const glm::ivec2 & size) const override;
            PAX_NODISCARD glm::vec4 getPixelOfChannelAt(const std::string & channelName, const glm::ivec2 & pos) const override;
        };
    }
}

#endif //PAXENGINE3_OPENGLRENDERPASS_H
