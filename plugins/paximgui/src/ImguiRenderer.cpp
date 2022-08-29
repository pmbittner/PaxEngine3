//
// Created by Paul on 29.08.2022.
//

#include "paximgui/ImguiRenderer.h"
#include "paximgui/ImguiPlugin.h"

#include "imgui.h"

namespace PAX {
    namespace Imgui {
        ImguiRenderer::ImguiRenderer(const PAX::Imgui::ImguiPlugin &plugin) : plugin(plugin) {}

        void ImguiRenderer::render(PAX::RenderOptions &renderOptions) {
            // At the beginning of your frame:
            plugin.ImGui_ImplXXXX_NewFrame();
            ImGui::NewFrame();

            SceneGraph::render(renderOptions);

            // At the end of your frame:
            ImGui::Render();
            plugin.ImGui_ImplXXXX_RenderDrawData();
        }
    }
}