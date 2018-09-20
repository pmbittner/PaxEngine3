//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_SDLENGINEPLUGIN_H
#define PAXENGINE3_SDLENGINEPLUGIN_H

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>
#include <paxcore/EnginePlugin.h>
#include <paxcore/service/Paths.h>
#include <paxcore/service/Services.h>
#include "SDLInputSystem.h"

namespace PAX {
    namespace SDL {
        class SDLEnginePlugin : public EnginePlugin {
        PAX_ENGINEPLUGIN_CONTAINS_ENTITYCOMPONENTS
            class SDLInputSystemFactory : public Factory<InputSystem> {
                virtual std::shared_ptr<InputSystem> create() {
                    return std::make_shared<SDLInputSystem>();
                }
            } inputSystemFactory;

        public:
            virtual void initialize(Engine& engine) override {
                LOG(INFO) << "initialize SDL";

                SDL_Init(SDL_INIT_EVERYTHING);
                //TTF_Init();
            };

            virtual void registerFactories(FactoryService& factoryService) override {
                factoryService.registerFactory(&inputSystemFactory);
            };
        };
    }
}

#endif //PAXENGINE3_SDLENGINEPLUGIN_H
