add_library(paxsdl SDLInputSystem.cpp SDLWindow.cpp SDLEngineSetup.cpp)
target_link_libraries(paxsdl ${SDL2_LIBRARY})