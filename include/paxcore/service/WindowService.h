//
// Created by paul on 02.12.18.
//

#ifndef PAXENGINE3_WINDOWSERVICE_H
#define PAXENGINE3_WINDOWSERVICE_H

#include <memory>
#include <paxcore/io/Window.h>

namespace PAX {
    class Services;

    class WindowService {
        friend class Services;

        std::shared_ptr<Window> _window = nullptr;

        WindowService();

        void initialize();
        void terminate();
    public:

        const std::shared_ptr<Window>& getWindow();
    };
}

#endif //PAXENGINE3_WINDOWSERVICE_H
