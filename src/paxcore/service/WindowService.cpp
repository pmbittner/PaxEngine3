//
// Created by paul on 02.12.18.
//

#include <paxcore/service/WindowService.h>
#include <paxcore/service/Services.h>

namespace PAX {
    WindowService::WindowService() = default;

    void WindowService::initialize() {
        Settings & globalSettings = Services::GetGlobalSettings();
        std::string title = globalSettings.getOrDefault<std::string>("core_windowTitle", "PaxEngine3");
        int resX = globalSettings.getOrDefault<int>("core_resolutionWidth", 800);
        int resY = globalSettings.getOrDefault<int>("core_resolutionHeight", 600);

        _window = Services::GetFactory().create<Window>(title.c_str(), resX, resY);

        if (globalSettings.getOrDefault<bool>("core_startInFullscreen")) {
            _window->setFullscreen(true);
        }
    }

    void WindowService::terminate() {
        _window->dispose();
    }

    const std::shared_ptr<Window>& WindowService::getWindow() {
        return _window;
    }
}