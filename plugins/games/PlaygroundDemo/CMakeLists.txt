project(PlaygroundDemo)

set(PAX_PLAYGROUNDDEMO_SOURCE_FILES src/main.cpp src/Plugin.cpp)

include_directories(include)
include_directories(../../paxsdl/include)
include_directories(../../paxopengl/include)
include_directories(../../paxassetimport/include)
set(HEADERS_FOR_CLION
        include/playgrounddemo/Plugin.h
        include/playgrounddemo/Demo.h)

add_executable(PlaygroundDemo ${PAX_PLAYGROUNDDEMO_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(PlaygroundDemo paxassimp paxutil paxsdl paxopengl paxcore)
set_target_properties(PlaygroundDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Demo)