//
// Created by paul on 19.05.18.
//

#include "paximgui/ImguiPlugin.h"

#include "paxcore/Engine.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "paxsdl/opengl/SDLOpenGLPlugin.h"
#include "paxopengl/OpenGLPlugin.h"

#include "paxsdl/SDLWindow.h"
#include "paxsdl/opengl/SDLOpenGLWindow.h"
#include "paxopengl/rendernodes/OpenGLContext.h"

namespace PAX {
    namespace Imgui {
        ImguiPlugin::ImguiPlugin()
        : imguiRenderer(*this)
        {}

        void ImguiPlugin::checkDependencies(const std::vector<EnginePlugin *> &plugins) const {
            static EnginePluginTypedDependencies<
                    PAX::OpenGL::OpenGLPlugin,
                    PAX::SDL::SDLPlugin,
                    PAX::SDL::OpenGL::SDLOpenGLPlugin>
                    dependencies("PAX::Imgui::ImguiPlugin");
            dependencies.checkDependencies(plugins);
        }

        void ImguiPlugin::hookInput() {
            InputSystem & inputSystem = Services::GetInput();
            if (auto * sdlInput = dynamic_cast<SDL::SDLInputSystem*>(&inputSystem)) {
                sdlInput->OnSDL_Event.add<ImguiPlugin, &ImguiPlugin::OnSDL_Input>(this);
                PAX_LOG(Log::Level::Info, "Hooked imgui input to SDL.");
            } else {
                PAX_LOG(Log::Level::Warn, "Failed hooking imgui input to SDL! Used InputSystem is not an SDL::SDLInputSystem!");
            }
        }

        void ImguiPlugin::unhookInput() {
            InputSystem & inputSystem = Services::GetInput();
            if (auto * sdlInput = dynamic_cast<SDL::SDLInputSystem*>(&inputSystem)) {
                sdlInput->OnSDL_Event.add<ImguiPlugin, &ImguiPlugin::OnSDL_Input>(this);
                PAX_LOG(Log::Level::Info, "Unhooked imgui input from SDL.");
            } else {
                PAX_LOG(Log::Level::Warn, "Failed unhooking imgui input from SDL! Used InputSystem is not an SDL::SDLInputSystem!");
            }
        }

        void ImguiPlugin::hookRendering() {
            Renderer & renderer = Engine::Instance().getRenderer();
            TypedSceneGraph<Renderable> * oldRoot = renderer.getSceneGraphGenerationEntryPoint();
            auto * openGlContext = dynamic_cast<OpenGL::OpenGLContext*>(oldRoot);
            if (openGlContext == nullptr) {
                PAX_LOG(Log::Level::Error, "Failed hooking imgui rendering! Assertion that the initial scene graph generation entry point is an OpenGL::OpenGLContext failed!");
                return;
            }

            // get all children of the current generation entry point and add them to our renderer
            for (Renderable * childOfOpenGLContext : openGlContext->getChildren()) {
                imguiRenderer.addChild(childOfOpenGLContext);
            }
            // then remove the children from the old entry point
            openGlContext->dropChildren();
            // and add our renderer below the old entry point
            openGlContext->addChild(&imguiRenderer);
            renderer.setSceneGraphGenerationEntryPoint(&imguiRenderer);
        }

        void ImguiPlugin::initialize(Engine &engine) {}

        void ImguiPlugin::postInitialize(Engine &engine) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            const auto& windowAsSDLType = std::dynamic_pointer_cast<PAX::SDL::OpenGL::SDLOpenGLWindow>(Services::GetWindowService().getWindow());

            ImGui_ImplSDL2_InitForOpenGL(
                    windowAsSDLType->getSDL_Window(),
                    windowAsSDLType->getContext()
                    );
            ImGui_ImplOpenGL3_Init(PAX_HARDCODED_GLSL_VERSION);

//            ImGui::StyleColorsLight();
            ImGui::StyleColorsClassic();
//            ImGui::StyleColorsDark();

            hookInput();
            hookRendering();
        }

        void ImguiPlugin::terminate(PAX::Engine &engine) {
            unhookInput();

            ImGui_ImplSDL2_Shutdown();
            ImGui_ImplOpenGL3_Shutdown();
            ImGui::DestroyContext();
        }

        void ImguiPlugin::OnSDL_Input(const SDL_Event * event) {
            ImGui_ImplSDL2_ProcessEvent(event);
        }

        void ImguiPlugin::ImGui_ImplXXXX_NewFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
        }

        void ImguiPlugin::ImGui_ImplXXXX_RenderDrawData() {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
}