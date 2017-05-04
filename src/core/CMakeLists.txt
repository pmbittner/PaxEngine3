set(CORE_SOURCE_FILES Engine.cpp Game.cpp InputSystem.cpp)

add_subdirectory(entity)
add_subdirectory(io)
add_subdirectory(rendering)

add_library(paxcore ${CORE_SOURCE_FILES})
target_link_libraries(paxcore ${SDL2_LIBRARY})