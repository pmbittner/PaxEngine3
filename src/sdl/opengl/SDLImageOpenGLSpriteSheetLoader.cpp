//
// Created by Paul on 07.01.2018.
//

#include <sdl/opengl/SDLImageOpenGLSpriteSheetLoader.h>
#include <opengl/resource/OpenGLTexture2D.h>

#ifdef PAX_WITH_SDLIMAGE
#include <SDL2/SDL_image.h>
#endif

#include <lib/easylogging++.h>
#include <utility/io/FormatChecker.h>
#include <assert.h>
#include <opengl/resource/OpenGLSpriteSheet.h>
#include <opengl/utility/Error.h>

namespace PAX {
    namespace OpenGL {
        SDLImageOpenGLSpriteSheetLoader::SDLImageOpenGLSpriteSheetLoader() {

        }

        SDLImageOpenGLSpriteSheetLoader::~SDLImageOpenGLSpriteSheetLoader() {

        }

        bool SDLImageOpenGLSpriteSheetLoader::canLoad(Path path, int cellWidth, int cellHeight) {
            Util::FormatChecker formats({
                "BMP", "GIF", "JPEG", "LBM", "PCX", "PNG", "PNM", "SVG", "TGA", "TIFF", "WEBP", "XCF", "XPM", "XV"
            });
            return formats.check(path);
        }

        PAX::SpriteSheet *PAX::OpenGL::SDLImageOpenGLSpriteSheetLoader::load(Path path, int cellWidth, int cellHeight) {
#ifdef PAX_WITH_SDLIMAGE
            catchError("SDLImageOpenGLSpriteSheetLoader: start");
            SDL_Surface* sdlTexture = NULL;

            int flags = IMG_INIT_JPG | IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if((initted & flags) != flags) {
                LOG(ERROR) << "could not init SDL_Image: " << IMG_GetError();
            }

            if((sdlTexture = IMG_Load(path)) == NULL) {
                LOG(ERROR) << "Loading texture " << path << " failed in SDLImageOpenGLSpriteSheetLoader.";
            }

            int totalWidth = sdlTexture->w;
            int totalHeight = sdlTexture->h;
            int index = 0;

            if (totalWidth % cellWidth != 0 || totalHeight % cellHeight != 0) {
                LOG(WARNING) << "Loading SpriteSheet " << path << " of size (" << totalWidth << ", " << totalHeight << ") with cell size ("
                             << cellWidth << ", " << cellHeight << ") aborted. The texture size is not a multiple of the cell size!";
                SDL_FreeSurface(sdlTexture);
                return nullptr;
            }

            GLenum inputFormat = GL_RGB;
            if(sdlTexture->format->BytesPerPixel == 4) {
                inputFormat = GL_RGBA;
            }

            int spriteCount = (totalWidth / cellWidth) * (totalHeight / cellHeight);
            OpenGLSpriteSheet *spriteSheet = new OpenGLSpriteSheet(spriteCount);

            GLuint *ids = new GLuint[spriteCount];
            catchError("SDLImageOpenGLSpriteSheetLoader: berfore glGenTextures");
            glGenTextures(spriteCount, ids);
            catchError("SDLImageOpenGLSpriteSheetLoader: glGenTextures");

            for (int y = 0; y < totalHeight; y += cellHeight) {
                for (int x = 0; x < totalWidth; x += cellWidth) {
                    std::cout << "Creating texture at index " << index << " with id " << ids[index]  << std::endl;
                    spriteSheet->setOpenGLTextureAt(index, OpenGLTexture2D(ids[index], cellWidth, cellHeight));
                    OpenGLTexture2D &texture = spriteSheet->getOpenGLTextureAt(index);

                    texture.bind();
                    catchError("SDLImageOpenGLSpriteSheetLoader: texture.bind");
                    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
                    catchError("SDLImageOpenGLSpriteSheetLoader: before glPixelStorei GL_UNPACK_ALIGNMENT");

                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

                    glTexImage2D(GL_TEXTURE_2D, 0, inputFormat, cellWidth, cellHeight, 0/*border*/, inputFormat, GL_UNSIGNED_BYTE, nullptr);
                    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, cellWidth, cellHeight, inputFormat, GL_UNSIGNED_BYTE, sdlTexture->pixels);
                    catchError("SDLImageOpenGLSpriteSheetLoader: after glTexSubImage2D");
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);;

                    texture.unbind();

                    ++index;
                }
            }

            SDL_FreeSurface(sdlTexture);
            delete[] ids;

            return spriteSheet;
#else
            assert(false);
            return nullptr;
#endif
        }

        bool SDLImageOpenGLSpriteSheetLoader::free(SpriteSheet *res) {
            if (res) {
                OpenGLSpriteSheet* spriteSheet = static_cast<OpenGLSpriteSheet*>(res);
                int spriteCount = spriteSheet->getTextureCount();

                GLuint *ids = new GLuint[spriteCount];
                for (int i = 0; i < spriteCount; ++i) {
                    ids[i] = spriteSheet->getOpenGLTextureAt(i).getID();
                }
                glDeleteTextures(1, ids);
                delete[] ids;

                delete res;
                return true;
            }

            return false;
        }
    }
}