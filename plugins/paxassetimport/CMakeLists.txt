find_package(assimp REQUIRED)

set(PAX_ASSIMP_SOURCE_FILES
        src/Plugin.cpp
        src/AssimpResourceLoader.cpp)

add_library(paxassimp ${PAX_ASSIMP_SOURCE_FILES})
add_library(PaxEngine3::assimp ALIAS paxassimp)
target_include_directories(paxassimp PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxassimp PUBLIC paxcore assimp::assimp)
