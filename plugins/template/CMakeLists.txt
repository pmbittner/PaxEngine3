project(PaxTemplatePlugin)

set(HEADERS_FOR_CLION include/Plugin.h include/FollowEntityBehaviour.h)
set(SOURCE_FILES src/Plugin.cpp ${HEADERS_FOR_CLION})

include_directories(include)
add_library(TemplatePlugin ${SOURCE_FILES})