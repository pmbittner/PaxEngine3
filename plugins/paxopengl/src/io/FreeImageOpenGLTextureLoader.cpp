//
// Created by Paul on 13.10.2017.
//

#include "io/FreeImageOpenGLTextureLoader.h"
#include <GL/glew.h>
#include "resource/OpenGLTexture2D.h"


#ifdef PAX_WITH_FREEIMAGE
#define FREEIMAGE_LIB
#include <FreeImage.h>
#endif

namespace PAX {
    namespace OpenGL {
        FreeImageOpenGLTextureLoader::FreeImageOpenGLTextureLoader() {
#ifdef FREEIMAGE_LIB
            FreeImage_Initialise();
#endif
        }

        FreeImageOpenGLTextureLoader::~FreeImageOpenGLTextureLoader() {
#ifdef FREEIMAGE_LIB
            FreeImage_DeInitialise();
#endif
        }

        bool PAX::OpenGL::FreeImageOpenGLTextureLoader::canLoad(const char *path) const {
            return true;
        }

        std::shared_ptr<PAX::Texture> PAX::OpenGL::FreeImageOpenGLTextureLoader::load(const char *path) {
#ifdef PAX_WITH_FREEIMAGE
            GLenum image_format = GL_RGB;		//format the image is in
            GLint internal_format = GL_RGB;		//format to store the image in
            GLint level = 0;					//mipmapping level
            GLint border = 0;					//border size

            //image format
            FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
            //pointer to the image, once loaded
            FIBITMAP *dib(0);
            //pointer to the image data
            BYTE* bits(0);
            //image width and height
            unsigned int width(0), height(0);
            //OpenGL's image ID to map to
            GLuint gl_texID;

            //check the file signature and deduce its format
            fif = FreeImage_GetFileType(path, 0);
            //if still unknown, try to guess the file format from the file extension
            if(fif == FIF_UNKNOWN)
                fif = FreeImage_GetFIFFromFilename(path);
            //if still unkown, return failure
            if(fif == FIF_UNKNOWN)
                return nullptr;

            //check that the plugin has reading capabilities and load the file
            if(FreeImage_FIFSupportsReading(fif))
                dib = FreeImage_Load(fif, path);
            //if the image failed to load, return failure
            if(!dib)
                return nullptr;

            //retrieve the image data
            bits = FreeImage_GetBits(dib);
            //get the image width and height
            width = FreeImage_GetWidth(dib);
            height = FreeImage_GetHeight(dib);
            //if this somehow one of these failed (they shouldn't), return failure
            if((bits == 0) || (width == 0) || (height == 0))
                return nullptr;

            //generate an OpenGL texture ID for this texture
            glGenTextures(1, &gl_texID);
            //bind to the new texture ID
            glBindTexture(GL_TEXTURE_2D, gl_texID);
            //store the texture data for OpenGL use
            glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
                         border, image_format, GL_UNSIGNED_BYTE, bits);

            //Free FreeImage's copy of the data
            FreeImage_Unload(dib);

            //return success
            return std::make_shared<OpenGLTexture2D>(gl_texID, width, height);
#else
            return nullptr;
#endif
        }
    }
}