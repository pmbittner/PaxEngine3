set(HEADERS)

set(SOURCES)

add_library(paxecs ${HEADERS} ${SOURCES})
target_link_libraries(paxecs paxutil)