add_library(paxsdl SDLInputSystem.cpp SDLWindow.cpp SDLEngineSetup.cpp test/SDLSprite.cpp)
target_link_libraries(paxsdl ${SDL2_LIBRARY})