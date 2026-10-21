set(PAX_PLAYGROUNDDEMO_SOURCE_FILES src/main.cpp src/Plugin.cpp)

add_executable(PlaygroundDemo ${PAX_PLAYGROUNDDEMO_SOURCE_FILES})
target_link_libraries(PlaygroundDemo PRIVATE paxsdl paxopengl paxassimp)
target_include_directories(PlaygroundDemo PRIVATE include)
set_target_properties(PlaygroundDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Demo)
