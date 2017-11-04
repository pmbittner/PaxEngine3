//
// Created by Paul on 04.11.2017.
//

#include <sdl/opengl/SDLImageOpenGLTextureLoader.h>
#include <GL/glew.h>
#include <opengl/resource/OpenGLTexture2D.h>

#include <SDL.h>
#include <SDL_image.h>
#include <lib/easylogging++.h>
#include <utility/io/FormatChecker.h>

namespace PAX {
    namespace OpenGL {
        SDLImageOpenGLTextureLoader::SDLImageOpenGLTextureLoader() {

        }

        SDLImageOpenGLTextureLoader::~SDLImageOpenGLTextureLoader() {

        }

        bool PAX::OpenGL::SDLImageOpenGLTextureLoader::canLoad(const char *path) {
            // BMP, GIF, JPEG, LBM, PCX, PNG, PNM, SVG, TGA, TIFF, WEBP, XCF, XPM, XV
            Util::FormatChecker formats({
                    "BMP", "GIF", "JPEG", "LBM", "PCX", "PNG", "PNM", "SVG", "TGA", "TIFF", "WEBP", "XCF", "XPM", "XV"
            });
            return formats.check(path);
        }

        PAX::Texture *PAX::OpenGL::SDLImageOpenGLTextureLoader::load(const char *path) {
#ifdef PAX_WITH_SDLIMAGE
            SDL_Surface* tex = NULL;

            int flags = IMG_INIT_JPG | IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if((initted & flags) != flags) {
                LOG(ERROR) << "could not init SDL_Image: " << IMG_GetError();
            }

            if((tex = IMG_Load(path)) == NULL) {
                LOG(ERROR) << "Loading texture " << path << " failed in OpenGLTexture2D.";
            }

            GLuint id;
            glGenTextures(1, &id);

            OpenGLTexture2D *ogltexture = new OpenGLTexture2D(id, tex->w, tex->h);

            ogltexture->bind();

            int Mode = GL_RGB;
            if(tex->format->BytesPerPixel == 4) {
                Mode = GL_RGBA;
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
            glTexImage2D(GL_TEXTURE_2D, 0, Mode, ogltexture->getWidth(), ogltexture->getHeight(), 0, Mode, GL_UNSIGNED_BYTE, tex->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            ogltexture->unbind();


            SDL_FreeSurface(tex);

            return ogltexture;
#else
            return new OpenGLTexture2D(0);
#endif
        }

        bool PAX::OpenGL::SDLImageOpenGLTextureLoader::free(Texture *res) {
            delete res;
        }
    }
}