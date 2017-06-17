add_subdirectory(sdl)
add_subdirectory(opengl)
add_subdirectory(core)
add_subdirectory(test)

#add_library(paxall core/Engine.cpp core/Game.cpp core/io/Keyboard.cpp core/io/Mouse.cpp core/entity/Entity.cpp rendering/Renderer.cpp test/SDLTestApplication2.cpp)
#target_link_libraries(paxall ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

#set(SOURCE_FILES ${SOURCE_FILES} core/Engine.cpp core/Game.cpp core/io/Keyboard.cpp core/io/Mouse.cpp core/entity/Entity.cpp rendering/Renderer.cpp test/SDLTestApplication2.cpp)