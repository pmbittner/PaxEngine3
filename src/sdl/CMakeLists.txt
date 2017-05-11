add_library(paxsdl SDLScreen.cpp SDLInputSystem.cpp)
target_link_libraries(paxsdl ${SDL2_LIBRARY})