set(HEADERS_FOR_CLION
        include/paxfont/Plugin.h
        include/paxfont/monospace/Text.h
        include/paxfont/monospace/Letter.h)

set(SOURCE_FILES
        src/Plugin.cpp
        src/monospace/Text.cpp src/monospace/Letter.cpp)

include_directories(include)

add_library(paxfont ${SOURCE_FILES} ${HEADERS_FOR_CLION})
#target_link_libraries(paxfont)