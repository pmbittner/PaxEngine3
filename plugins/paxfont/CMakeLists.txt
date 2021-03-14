set(HEADERS_FOR_CLION
        include/paxfont/Plugin.h
        include/paxfont/bitmap/BitmapFont.h
        include/paxfont/bitmap/BitmapText.h
        include/paxfont/bitmap/loader/XMLBitmapFontLoader.h)

set(SOURCE_FILES
        src/Plugin.cpp
        src/bitmap/BitmapFont.cpp
        src/bitmap/BitmapText.cpp
        src/bitmap/loader/XMLBitmapFontLoader.cpp)

include_directories(include)

add_library(paxfont ${SOURCE_FILES} ${HEADERS_FOR_CLION})
#target_link_libraries(paxfont)