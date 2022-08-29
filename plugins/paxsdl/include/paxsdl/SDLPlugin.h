//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLENGINEPLUGIN_H
#define PAXENGINE3_SDLENGINEPLUGIN_H

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/service/Paths.h>
#include <paxcore/service/Services.h>
#include <paxcore/io/InputSystemFactory.h>
#include <polypropylene/log/Log.h>
#include <paxutil/resources/JsonResourceFieldWriter.h>
#include "SDLInputSystem.h"
#include "SDLTextureLoader.h"
#include "SDLImageLoader.h"

#include <paxcore/rendering/loader/NullTextureLoader.h>

namespace PAX {
    namespace SDL {
        class SDLPlugin : public EnginePlugin {
            class SDLInputSystemFactory : public InputSystemFactory {
                std::shared_ptr<InputSystem> create() override {
                    return std::make_shared<SDLInputSystem>();
                }
            } inputSystemFactory;

#ifdef PAX_WITH_SDLIMAGE
            SDLTextureLoader textureLoader;
            SDLImageLoader imageLoader;
            JsonResourceFieldWriter<Image> jsonImageParser;
#endif

        public:
            void initialize(Engine& engine) override {
                EnginePlugin::initialize(engine);

                PAX_LOG(Log::Level::Info, "initialize SDL");

                SDL_Init(SDL_INIT_EVERYTHING);
                //TTF_Init();
            }

            void terminate(Engine& engine) override {
                SDL_Quit();
                EnginePlugin::terminate(engine);
            }

            void registerFactories(FactoryService& factoryService) override {
                factoryService.set(paxtypeid(InputSystemFactory), &inputSystemFactory);
            }

            void registerResourceLoaders(Resources& resources) override {
#ifdef PAX_WITH_SDLIMAGE
                Services::GetResources().registerLoader<Texture>(&textureLoader);
                Services::GetResources().registerLoader<Image>(&imageLoader);
#endif
            }

            void registerJsonWriters(Json::JsonFieldWriterRegister & writerRegister) override {
#ifdef PAX_WITH_SDLIMAGE
                jsonImageParser.registerAt(writerRegister);
#endif
            }
        };
    }
}

#endif //PAXENGINE3_SDLENGINEPLUGIN_H
