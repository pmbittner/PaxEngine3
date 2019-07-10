### LIBRARIES ########################################


set(PAXVULKAN_HEADERS_FOR_CLION
        include/paxvulkan/VulkanPlugin.h)

set(PAXVULKAN_SOURCE_FILES
        src/VulkanPlugin.cpp)

### TARGET ###########################################
include_directories(include)

add_library(paxvulkan
        ${PAXVULKAN_HEADERS_FOR_CLION}
        ${PAXVULKAN_SOURCE_FILES})

#target_link_libraries(paxvulkan)