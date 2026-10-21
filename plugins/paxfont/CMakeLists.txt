set(SOURCE_FILES
        src/Plugin.cpp
        src/bitmap/BitmapFont.cpp
        src/bitmap/BitmapText.cpp
        src/bitmap/loader/XMLBitmapFontLoader.cpp)

add_library(paxfont ${SOURCE_FILES})
add_library(PaxEngine3::font ALIAS paxfont)
target_include_directories(paxfont PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxfont PUBLIC paxcore)
