find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::AssetImport ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMENT "Precompiling Assimp Model Loader (via Python)"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        VERBATIM
)

# Assimp

set(ASSIMP_DIRECTORY ${LIB_DIR}/assimp)
include_directories(${ASSIMP_DIRECTORY}/include)

##

include_directories(include)
set(HEADERS_FOR_CLION include/Plugin.h include/AssimpResourceLoader.h)
add_library(paxassimp ${HEADERS_FOR_CLION} src/Plugin.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp src/AssimpResourceLoader.cpp)