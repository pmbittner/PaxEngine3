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
set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY})
set(ASSIMP_LIBRARY_NAME)
set(ASSIMP_IRRXML_NAME)
set(ASSIMP_ZLIB_NAME)

if (WIN32)
    if (${COMPILER_IS_MSVC})
        message("Building PaxAssimp with MSVC")
        set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/cmake-build-release-msvc)
        set(ASSIMP_LIBRARY_NAME assimp-vc140-mt.lib)
        set(ASSIMP_IRRXML_NAME)
        set(ASSIMP_ZLIB_NAME)
    elseif(${COMPILER_IS_GCC})
        message("Building PaxAssimp with MinGW")
        set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/cmake-build-release-mingw)
        set(ASSIMP_LIBRARY_NAME libassimp.a)
        set(ASSIMP_IRRXML_NAME libIrrXML.a)
        set(ASSIMP_ZLIB_NAME libzlibstatic.a)
    endif(${COMPILER_IS_MSVC})
endif(WIN32)
# TODO: case for LINUX

set(ASSIMP_ASSIMP_DIR ${ASSIMP_BUILD_DIRECTORY}/code)
set(ASSIMP_IRRXML_DIR ${ASSIMP_BUILD_DIRECTORY}/contrib/irrXML)
set(ASSIMP_ZLIB_DIR ${ASSIMP_BUILD_DIRECTORY}/contrib/zlib)

set(ASSIMP_LIBRARY_DIRECTORIES ${ASSIMP_ASSIMP_DIR} ${ASSIMP_IRRXML_DIR} ${ASSIMP_ZLIB_DIR})
set(ASSIMP_LIBRARIES ${ASSIMP_ASSIMP_DIR}/${ASSIMP_LIBRARY_NAME} ${ASSIMP_IRRXML_DIR}/${ASSIMP_IRRXML_NAME} ${ASSIMP_ZLIB_DIR}/${ASSIMP_ZLIB_NAME})

include_directories(${ASSIMP_DIRECTORY}/include)
include_directories(${ASSIMP_BUILD_DIRECTORY}/include)
link_directories(${ASSIMP_LIBRARY_DIRECTORIES})

##

include_directories(include)
set(HEADERS_FOR_CLION include/Plugin.h include/AssimpResourceLoader.h)
add_library(paxassimp ${HEADERS_FOR_CLION} src/Plugin.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp src/AssimpResourceLoader.cpp)
target_link_libraries(paxassimp ${ASSIMP_LIBRARIES})