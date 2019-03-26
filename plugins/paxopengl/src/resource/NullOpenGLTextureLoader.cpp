//
// Created by bittner on 11/20/17.
//

#include <vector>
#include <GL/glew.h>
#include <paxutil/math/Conversion.h>

#include "paxopengl/resource/NullOpenGLTextureLoader.h"

namespace PAX {
    namespace OpenGL {
        NullOpenGLTextureLoader::NullOpenGLTextureLoader() = default;

        NullOpenGLTextureLoader::~NullOpenGLTextureLoader() = default;

        bool NullOpenGLTextureLoader::canLoad(Path path) const {
            return true;
        }

        std::shared_ptr<PAX::Texture> NullOpenGLTextureLoader::load(Path path) {
            if (!_texture) {
                int w = 16;
                int h = w;

                int mode = GL_RGB;
                int pixelCount = w * h;
                std::vector<char> pixels(pixelCount * 3);

                struct Pixel {
                    int x;
                    int y;
                };
                int xoffset = 6;//2 for 8x8 pixels
                int yoffset = 5;//1 for 8x8 pixels
                std::vector<Pixel> errorLetter = {
                        {0, 0},
                        {1, 0},
                        {2, 0},
                        {3, 0},
                        {0, 1},
                        {0, 2},
                        {1, 2},
                        {2, 2},
                        {0, 3},
                        {0, 4},
                        {0, 5},
                        {1, 5},
                        {2, 5},
                        {3, 5},
                };

                /*
                for (int i = 0; i < pixelCount; ++i) {
                    int index = 3*i;
                    pixels[index] = pixels[index+1] = pixels[index+2] = 0;
                }
                //*/

                for (Pixel &p: errorLetter) {
                    int index = 3 * PAX::Util::Conversion::coordinatesToIndex(w, p.x + xoffset, p.y + yoffset);
                    pixels[index] = 255;
                    pixels[index + 1] = 0;
                    pixels[index + 2] = 0;
                }

                GLuint id;
                glGenTextures(1, &id);

                _texture = std::make_shared<OpenGLTexture2D>(id, w, h);

                _texture->bind();

                glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
                glTexImage2D(GL_TEXTURE_2D, 0, mode, _texture->getWidth(), _texture->getHeight(), 0, mode,
                             GL_UNSIGNED_BYTE, &pixels.front());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                _texture->unbind();
            }

            return _texture;
        }

        std::shared_ptr<Texture> NullOpenGLTextureLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                                   const PAX::VariableHierarchy &parameters) {
            return load(Path());
        }
    }
}