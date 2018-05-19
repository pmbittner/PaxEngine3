//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLENGINEPLUGIN_H
#define PAXENGINE3_SDLENGINEPLUGIN_H

#include <core/EnginePlugin.h>

#include <SDL2/SDL.h>
#include <core/service/Paths.h>
#include <sdl/utility/Path.h>
#include <core/service/Services.h>
//#include <SDL_ttf.h>
#include "SDLEngineSetup.h"
#include "SDLInputSystem.h"

namespace PAX {
    namespace SDL {
        class SDLEnginePlugin : public EnginePlugin {
            class SDLInputSystemFactory : public Factory<InputSystem> {
                virtual std::shared_ptr<InputSystem> create() {
                    return std::make_shared<SDLInputSystem>();
                }
            } inputSystemFactory;

        public:
            virtual void initialize(Engine& engine) override {
                LOG(INFO) << "    SDLEnginePlugin initialize";

                SDL_Init(SDL_INIT_EVERYTHING);
                //TTF_Init();

                Services::GetPaths().setExecutionDirectory(getBasePath());
            };

            virtual void registerFactories(FactoryService& factoryService) override {
                factoryService.registerFactory(&inputSystemFactory);
            };
        };
    }
}

#endif //PAXENGINE3_SDLENGINEPLUGIN_H
