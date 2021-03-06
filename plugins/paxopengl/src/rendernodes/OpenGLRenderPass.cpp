//
// Created by Bittner on 08.04.2019.
//

#include <paxopengl/rendernodes/OpenGLRenderPass.h>
#include <GL/glew.h>
#include <paxopengl/resource/OpenGLTexture2D.h>
#include <paxopengl/Conversion.h>
#include <paxopengl/OpenGLError.h>

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

            attachmentOfRenderPass.clear();

            //create a framebuffer and store its id, then bind it
            glGenFramebuffers(1, &fbo);
            RenderPassBinder.push({fbo});

            int i = 0;
            std::vector<GLenum> attachments;
            for (const RenderPassChannel & c : getChannels()) {
                OpenGLTexture2D * tex = dynamic_cast<OpenGLTexture2D*>(c.getTexture().get());
                if (!tex) {
                    PAX_THROW_RUNTIME_ERROR("Texture of channel " << c.getName() << " is not a OpenGLTexture2D!");
                }

                attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
                attachmentOfRenderPass[c.getName()] = attachments.back();
                glFramebufferTexture2D(GL_FRAMEBUFFER, attachments.back(), GL_TEXTURE_2D, tex->getID(), 0);

                ++i;
            }

            if (attachments.empty()) {
                attachments.push_back(GL_NONE);
            }

            glDrawBuffers(int(attachments.size()), &attachments[0]);

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

        std::shared_ptr<Image> OpenGLRenderPass::getPixelsOfChannel(const std::string &channelName,
                                                                    const glm::ivec2 &upperLeft,
                                                                    const glm::ivec2 &size) const {
            const auto & it = attachmentOfRenderPass.find(channelName);
            if (it != attachmentOfRenderPass.end()) {
                const std::shared_ptr<Texture> & channelTexture = getChannel(channelName).getTexture();
                GLenum attachment = it->second;

//                PAX_LOG(Log::Level::Info, channelName);
//                PAX_LOG(Log::Level::Info, "Attachement no = " << attachment - GL_COLOR_ATTACHMENT0);

                const int fromX = upperLeft.x;
                const int fromY = upperLeft.y;
                const int w = size.x;
                const int h = size.y;

#define PAX_OPENGL_ASSERT(cond) if (!(cond)) {PAX_THROW_RUNTIME_ERROR("Out of bounds: Assertion \"" << #cond << "\" failed");}
                PAX_OPENGL_ASSERT(fromX >= 0)
                PAX_OPENGL_ASSERT(fromY >= 0)
                PAX_OPENGL_ASSERT(fromX + w < channelTexture->getWidth())
                PAX_OPENGL_ASSERT(fromY + h < channelTexture->getHeight())
                PAX_OPENGL_ASSERT(channelTexture->getPixelFormat() == Texture::PixelFormat::RGBA)
#undef PAX_OPENGL_ASSERT
                std::shared_ptr<Image> img = std::make_shared<Image>(w, h);
//
//                img->getPixels()[100] = Colour(255, 255, 255, 255);

                RenderPassBinder.push({fbo, fbo});
                glReadBuffer(attachment);
//                glViewport(0, 0, w, h);
//                glReadBuffer(GL_FRONT);
                glReadPixels(fromX, fromY, w, h,
                             ToOpenGL(Texture::PixelFormat::RGBA),
                             GL_UNSIGNED_BYTE,
                             img->getPixels());
                RenderPassBinder.pop();
//                img->getPixels()[100] = Colour(255, 0, 255, 255);

                getGLError("OpenGLRenderPass::getPixelsOfChannel");

                return img;
            }
            PAX_THROW_RUNTIME_ERROR("There is no RenderPassChannel with the given name \"" << channelName << "\"!");
        }

        glm::vec4 OpenGLRenderPass::getPixelOfChannelAt(const std::string &channelName, const glm::ivec2 &pos) const {
            const auto & it = attachmentOfRenderPass.find(channelName);
            if (it != attachmentOfRenderPass.end()) {
                const std::shared_ptr<Texture> & channelTexture = getChannel(channelName).getTexture();
                GLenum attachment = it->second;

                const int fromX = pos.x;
                const int fromY = pos.y;
                const int w = 1;
                const int h = 1;

#define PAX_OPENGL_ASSERT(cond) if (!(cond)) {PAX_THROW_RUNTIME_ERROR("Out of bounds: Assertion \"" << #cond << "\" failed");}
                PAX_OPENGL_ASSERT(fromX >= 0)
                PAX_OPENGL_ASSERT(fromY >= 0)
                PAX_OPENGL_ASSERT(fromX < channelTexture->getWidth())
                PAX_OPENGL_ASSERT(fromY < channelTexture->getHeight())
#undef PAX_OPENGL_ASSERT
                glm::vec4 pixel(0, 0, 0, 0);

                RenderPassBinder.push({fbo, fbo});
                glReadBuffer(attachment);
                glReadPixels(fromX, fromY, w, h, ToOpenGL(channelTexture->getPixelFormat()), GL_FLOAT, &pixel);
                RenderPassBinder.pop();

                return pixel;
            }
            PAX_THROW_RUNTIME_ERROR("There is no RenderPassChannel with the given name \"" << channelName << "\"!");
        }
    }
}