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

#### ANTLR LIB

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    set(ANTLR_DIRECTORY ${PAX_LIB_DIR}/antlr4/runtime/Cpp)

    # Normally, the antlr lib is only called antlr4-runtime-static.lib but I renamed it to contain the suffix -debug or -release for the respective build.
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Including ANTLR with MSVC - Debug")
        set(ANTLR_LIBRARY ${ANTLR_DIRECTORY}/dist/antlr4-runtime-static-debug.lib)
    else()
        message("Including ANTLR with MSVC - Release")
        set(ANTLR_LIBRARY ${ANTLR_DIRECTORY}/dist/antlr4-runtime-static-release.lib)
    endif()

    include_directories(${ANTLR_DIRECTORY}/runtime/src)

    set(ANTLR_IMGUIPP_SOURCE_FILES
            imguipp_antlr/ImguiPPLexer.cpp
            imguipp_antlr/ImguiPPLexer.h
            imguipp_antlr/ImguiPPParser.cpp
            imguipp_antlr/ImguiPPParser.h
            imguipp_antlr/ImguiPPParserBaseListener.cpp
            imguipp_antlr/ImguiPPParserBaseListener.h
            imguipp_antlr/ImguiPPParserBaseVisitor.cpp
            imguipp_antlr/ImguiPPParserBaseVisitor.h
            imguipp_antlr/ImguiPPParserListener.cpp
            imguipp_antlr/ImguiPPParserListener.h
            imguipp_antlr/ImguiPPParserVisitor.cpp
            imguipp_antlr/ImguiPPParserVisitor.h
            )

    include_directories(imguipp_antlr)
    add_library(imguipp ${ANTLR_IMGUIPP_SOURCE_FILES})
else()
    message("ANTLR build not configured for NON-Windows OS.")
endif()


#### Plugin Dependencies

include_directories(../paxsdl/include/)
include_directories(../paxopengl/include/)

#### Plugin

set(PAX_IMGUI_HEADERS_FOR_CLION
        include/paximgui/ImguiPlugin.h
        include/paximgui/ImguiRenderer.h
        include/paximgui/Variable.h
        include/paximgui/ImguiUniformDetector.h include/paximgui/ImguiUniformDetectorVisitor.h)

set(PAX_IMGUI_SOURCE_FILES
        src/ImguiPlugin.cpp
        src/ImguiRenderer.cpp
        src/Variable.cpp src/ImguiUniformDetector.cpp src/ImguiUniformDetectorVisitor.cpp)

include_directories(include)

add_library(paximgui
        ${PAX_IMGUI_HEADERS_FOR_CLION}
        ${PAX_IMGUI_SOURCE_FILES}
        )
target_link_libraries(paximgui imgui imguipp ${ANTLR_LIBRARY})