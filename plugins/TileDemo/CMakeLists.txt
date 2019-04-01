project(TileDemo)

set(PAX_TILEDEMO_SOURCE_FILES
        src/main.cpp
        src/Plugin.cpp)

include_directories(include)
include_directories(../paxsdl/include)
include_directories(../paxopengl/include)
include_directories(../paxtiles/include)

set(HEADERS_FOR_CLION
        include/tiledemo/Plugin.h
        include/tiledemo/Demo.h)

add_executable(TileDemo ${PAX_TILEDEMO_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(TileDemo ${EASYLOGGING_LIBRARY} paxutil paxsdl paxopengl paxtiles paxcore)
set_target_properties(TileDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Demo)