//
// Created by paul on 19.05.18.
//

#ifndef PAXENGINE3_IMGUILPLUGIN_H
#define PAXENGINE3_IMGUILPLUGIN_H

#include <paxcore/plugin/EnginePlugin.h>
#include "SDL2/SDL_events.h"

#include "ImguiRenderer.h"

#define PAX_HARDCODED_GLSL_VERSION "#version 400"

namespace PAX {
    namespace Imgui {
        class ImguiPlugin : public EnginePlugin {
            ImguiRenderer imguiRenderer;

            void hookInput();
            void unhookInput();

            void hookRendering();

        public:
            ImguiPlugin();

            void checkDependencies(const std::vector<EnginePlugin*> & plugins) const override;

            void initialize(Engine& engine) override;
            void postInitialize(Engine& engine) override;
            void terminate(Engine& engine) override;

            static void ImGui_ImplXXXX_NewFrame() ;
            static void ImGui_ImplXXXX_RenderDrawData() ;
            void OnSDL_Input(const SDL_Event * event);
        };
    }
}

#endif //PAXENGINE3_IMGUILPLUGIN_H
