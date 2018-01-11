//
// Created by Paul on 02.07.2017.
//

#include <lib/easylogging++.h>
#include <core/service/Services.h>
#include <opengl/resource/OpenGLShaderLoader.h>
#include <opengl/resource/NullOpenGLTextureLoader.h>
#include <opengl/io/FreeImageOpenGLTextureLoader.h>
#include <sdl/opengl/SDLImageOpenGLTextureLoader.h>
#include "../../../include/sdl/opengl/SDLOpenGLEngineSetup.h"
#include "../../../include/opengl/OpenGLRenderFactory.h"
#include "../../../include/sdl/opengl/SDLOpenGLWindow.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            Window* SDLOpenGLEngineSetup::createWindow() {
                return new SDLOpenGLWindow();
            }

            RenderFactory * SDLOpenGLEngineSetup::createRenderFactory() {
                return new PAX::OpenGL::OpenGLRenderFactory();
            }

            void SDLOpenGLEngineSetup::registerServices() {
                LOG(INFO) << "Registering Services:";
                SDLEngineSetup::registerServices();

                LOG(INFO) << "    OpenGLShaderLoader";
                PAX::OpenGL::OpenGLShaderLoader *shaderLoader = new PAX::OpenGL::OpenGLShaderLoader();
                Services::GetResources().registerLoader<Shader>(static_cast<ResourceLoader<Shader, Path, Path>*>(shaderLoader));
                Services::GetResources().registerLoader<Shader>(static_cast<ResourceLoader<Shader, Shader::Flags, Path, Path>*>(shaderLoader));

#ifdef PAX_WITH_FREEIMAGE
#define PAX_IMAGE_LOADER_FOUND
                LOG(INFO) << "    FreeImageOpenGLTextureLoader";
                Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::FreeImageOpenGLTextureLoader());
#endif

#ifdef PAX_WITH_SDLIMAGE
#define PAX_IMAGE_LOADER_FOUND
                LOG(INFO) << "    SDLImageOpenGLTextureLoader";
                Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::SDLImageOpenGLTextureLoader());
#endif

#ifndef PAX_IMAGE_LOADER_FOUND
                LOG(WARNING) << "    NullImageOpenGLTextureLoader (No real image loaders were registered!)";
                Services::GetResources().registerLoader<Texture>(new PAX::OpenGL::NullOpenGLTextureLoader());
#endif
            }
        }
    }
}