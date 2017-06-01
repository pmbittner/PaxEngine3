//
// Created by Paul on 29.04.2017.
//

#include "../../../include/core/rendering/Renderer.h"
#include "../../../include/test/SDLTestApplication2.h"
#include "../../../include/core/Engine.h"

namespace PAX {
    void Renderer::initialize() {
        _sceneGraphBuilder.initialize(Engine::GetInstance()->getEventService());
    }

    void Renderer::render() {
        SDL_TEST_APPLICATION2::render();
    }
}