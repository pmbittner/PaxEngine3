//
// Created by Bittner on 08.04.2019.
//

#include <paxopengl/rendernodes/OpenGLRenderPass.h>
#include <GL/glew.h>
#include <paxopengl/resource/OpenGLTexture2D.h>

namespace PAX {
    namespace OpenGL {
        OpenGLRenderPass::RenderPassBind OpenGLRenderPass::RenderPassBinder;

        OpenGLRenderPass::RenderPassBind::Passes::Passes(GLuint drawBuffer, GLuint readBuffer) :
        drawBuffer(drawBuffer), readBuffer(readBuffer) {}

        void OpenGLRenderPass::RenderPassBind::push(PAX::OpenGL::OpenGLRenderPass::RenderPassBind::Passes p) {
            frameBuffers.push(p);
            bindTop();
        }

        void OpenGLRenderPass::RenderPassBind::pop() {
            frameBuffers.pop();
            bindTop();
        }

        void OpenGLRenderPass::RenderPassBind::bindTop() {
            if (frameBuffers.empty()) {
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
                glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
            } else {
                Passes & p = frameBuffers.top();
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, p.drawBuffer);
                glBindFramebuffer(GL_READ_FRAMEBUFFER, p.readBuffer);
            }
        }

        OpenGLRenderPass::OpenGLRenderPass(const glm::ivec2 & resolution) : RenderPass(resolution) {}
        OpenGLRenderPass::~OpenGLRenderPass() = default;

        void OpenGLRenderPass::finalize() {
            RenderPass::finalize();
            //create a framebuffer and store its id, then bind it
            glGenFramebuffers(1, &fbo);
            RenderPassBinder.push({fbo});

            int i = 0;
            std::vector<GLenum> attachements;
            for (const RenderPassChannel & c : getChannels()) {
                OpenGLTexture2D * tex = dynamic_cast<OpenGLTexture2D*>(c.getTexture().get());
                if (!tex) {
                    PAX_THROW_RUNTIME_ERROR("Texture of channel " << c.getName() << " is not a OpenGLTexture2D!");
                }

                attachements.emplace_back(GL_COLOR_ATTACHMENT0 + i);
                glFramebufferTexture2D(GL_FRAMEBUFFER, attachements.back(), GL_TEXTURE_2D, tex->getID(), 0);

                ++i;
            }

            if (!attachements.empty()) {
                attachements.push_back(GL_NONE);
            }

            glDrawBuffers(int(attachements.size()), &attachements[0]);

            RenderPassBinder.pop();
        }

        void OpenGLRenderPass::render(RenderOptions &renderOptions) {
            RenderPassBinder.push({fbo});
            const Colour & c = getClearColour();
            glm::vec4 floatColour(c.r, c.g, c.b, c.a);
            floatColour /= 255.f;
            glClearColor(floatColour.r, floatColour.g, floatColour.b, floatColour.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            RenderPass::render(renderOptions);
            RenderPassBinder.pop();

            // TODO: FIX THIS DIRTY DIRTY HACK
            glClearColor(0.8, 0.8, 0.8, 1);
        }
    }
}