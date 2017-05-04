add_library(paxtest SDLTestApplication2.cpp)
target_link_libraries(paxtest paxcore ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})