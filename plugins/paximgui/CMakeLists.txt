#### IMGUI LIB

set(IMGUI_SOURCE_FILES
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_sdl.cpp)
include_directories(imgui)
add_library(imgui ${IMGUI_SOURCE_FILES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#### Plugin Dependencies

include_directories(../paxsdl/include/)
include_directories(../paxopengl/include/)

#### Plugin

set(PAX_IMGUI_HEADERS_FOR_CLION
        include/paximgui/ImguiPlugin.h
        include/paximgui/ImguiRenderer.h)

set(PAX_IMGUI_SOURCE_FILES
        src/ImguiPlugin.cpp
        src/ImguiRenderer.cpp)

include_directories(include)

add_library(paximgui
        ${PAX_IMGUI_HEADERS_FOR_CLION}
        ${PAX_IMGUI_SOURCE_FILES}
        )
target_link_libraries(paximgui imgui)