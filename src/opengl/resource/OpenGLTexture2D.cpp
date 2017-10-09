//
// Created by Paul on 30.06.2017.
//

#include <SDL.h>

#ifdef PAX_WITH_SDLIMAGE
#include <SDL_image.h>
#endif

#include "../../../include/opengl/resource/OpenGLTexture2D.h"
#include "../../../include/lib/easylogging++.h"

namespace PAX {
    namespace OpenGL {
        OpenGLTexture2D::OpenGLTexture2D(std::string path) {
#ifdef PAX_WITH_SDLIMAGE
            SDL_Surface* tex = NULL;

            int flags = IMG_INIT_JPG | IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if( (initted & flags) != flags) {
                LOG(WARNING) << "could not init SDL_Image: " << IMG_GetError();
            }

            if((tex = IMG_Load(path.c_str())) == NULL) {
                LOG(ERROR) << "Loading texture " << path << " failed in OpenGLTexture2D.";
            }

            _w = tex->w;
            _h = tex->h;

            glGenTextures(1, &_id);
            bind();

            int Mode = GL_RGB;
            if(tex->format->BytesPerPixel == 4) {
                Mode = GL_RGBA;
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
            glTexImage2D(GL_TEXTURE_2D, 0, Mode, _w, _h, 0, Mode, GL_UNSIGNED_BYTE, tex->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            unbind();

            SDL_FreeSurface(tex);
#endif
        }

        OpenGLTexture2D::~OpenGLTexture2D() {
            glDeleteTextures(1, &_id);
        }

        void OpenGLTexture2D::bind() {
            //glBindTexture(GL_TEXTURE_2D, _id);
        }

        void OpenGLTexture2D::unbind() {
            //glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}